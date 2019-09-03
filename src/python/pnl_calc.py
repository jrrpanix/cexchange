import sys
import datetime
import pandas as pd


class pnltrack:
    def __init__(self, asset):
        self.asset = asset
        self.qty = 0
        self.apx = 0
        self.buys = []
        self.ldate = None
        self.lqty  = None 
        self.lpx   = None
        self.real = 0
        self.unreal = 0
        self.proceeds = 0
        self.cost = 0
        self.pnl = 0
        
    def update(self, dt, qty, px):
        real = 0
        if abs(px) < 1e-2 :
            px = self.lpx
        if qty > 0 :
            self.buys.append([qty,px])
            self.apx = self.calc_avg_buy_px()
            #self.cost, self.proceeds = 0, 0
        if qty < 0 :
            self.cost += self.apx * abs(qty)
            self.proceeds += px * abs(qty)
            real = (px - self.apx) * abs(qty)
            self.update_buys(qty)
            self.apx = self.calc_avg_buy_px()
        self.qty += qty
        self.unreal = (px - self.apx)* self.qty
        self.real += real
        self.pnl = self.real + self.unreal
        self.ldate = dt
        self.lpx = px
        self.lqty = qty

    def update_buys(self, sell_qty):
        sq = abs(sell_qty)
        while sq > 0 and len(self.buys) > 0:
            if sq < self.buys[0][0]:
                self.buys[0][0] = self.buys[0][0] - sq
                break
            else:
                sq -= self.buys[0][0]
                del self.buys[0]
            

    def calc_avg_buy_px(self):
        q, wpx = 0.0, 0.0
        for qty_px in self.buys:
            q += qty_px[0]
            wpx += qty_px[0] * qty_px[1]
        if q == 0: return 0
        return wpx/q

    def header():
        print("%10s %6s %10s %10s %10s %10s %8s %8s %8s %8s %8s" %
              ("date", "coin", "totalqty", "avgpx", "txn_qty", "tnx_px", "proceeds", "cost", "realized", "unrealiz", "pnl"))

    def report(self):
        datestr = self.ldate.strftime("%Y-%m-%d")
        print("%s %6s %10.3f %10.3f %10.3f %10.3f %8.0f %8.0f %8.0f %8.0f %8.0f" %
              (datestr, self.asset, self.qty, self.apx, self.lqty, self.lpx, self.proceeds, self.cost, self.real, self.unreal, self.pnl))
        


class coinbase :

    def __init__(self, fname):
        df = pd.read_csv(fname, 
                         usecols=[0,1,2,3,4,5,6,7],
                         names=['date','txn_type','asset','qty', 'price', 'usd_amount', 'addr', 'notes'],
                         header=None,
                         skiprows=4)
        df['date'] = pd.to_datetime(df['date'], format='%m/%d/%Y')
        self.df=df
        assets = self.df['asset'].unique()
        pnltrack.header()
        for asset in assets:
            self.hist_pnl(asset)

    def hist_pnl(self, asset):
        adf = self.df[self.df['asset'] == asset]
        pnl = pnltrack(asset)
        for i in range(len(adf)):
            txn = adf.iloc[i]['txn_type']
            if txn != 'Buy' and txn != 'Sell' : continue
            dt , q, p = adf.iloc[i]["date"], adf.iloc[i]["qty"], adf.iloc[i]["price"]
            if txn == 'Sell' : q = -q
            pnl.update(dt, q, p)
            pnl.report()

class bitstamp:

    def __init__(self, fname) :
        df = pd.read_csv(fname)
        df['Amount'], df['AmountUnits'] = zip(*df['Amount'].map(bitstamp.split_units))
        df['Value'], df['ValueUnits'] = zip(*df['Value'].map(bitstamp.split_units))
        df['Rate'], df['RateUnits'] = zip(*df['Rate'].map(bitstamp.split_units))
        df['Fee'], df['FeeUnits'] = zip(*df['Fee'].map(bitstamp.split_units))
        df['Datetime'] = df['Datetime'].map(bitstamp.get_date)
        self.df = df
        pnltrack.header()
        self.hist_pnl("XRP")

    def hist_pnl(self, asset):
        adf = self.df[self.df['AmountUnits'] == asset]
        pnl = pnltrack(asset)
        for i in range(len(adf)):
            sub_type = adf.iloc[i]["Sub Type"]
            if sub_type != "Buy" and sub_type != "Sell" : continue
            dt, q, p = adf.iloc[i]["Datetime"], adf.iloc[i]["Amount"], adf.iloc[i]["Rate"]
            if sub_type == "Sell" : q = -q
            pnl.update(dt, q, p)
            pnl.report()
                    
    def get_date(sdate):
        months=["Jan","Feb","Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
        vals = sdate.split(" ") 
        mm = months.index(vals[0].strip(".")) + 1
        dd = int(vals[1].strip(","))
        yy = int(vals[2].strip(","))
        return datetime.datetime(yy, mm, dd)

    def split_units(col_data):
        if type(col_data) == float:
            return 0, 'Nan'
        av = col_data.split(" ")
        if len(av) == 1:
            return 0, av[0]
        return float(av[0]), av[1]

class gdax:

    def __init__(self, fname):
        df = pd.read_csv(fname,
                         usecols=[0,1,2,3,4,5,6,7],
                         names=['type','time','amount','balance', 'unit', 'transferid', 'tradeid', 'orderid'],
                         header=None,
                         skiprows=1)
        df['time'] = df['time'].map(gdax.get_date)
        for i in range(len(df)):
            l = df.iloc[i]
            if l["type"] == "fee" : continue
            if l["unit"] != "BTC" and l["unit"] != "USD" : continue
            t, a, b, u = l["time"], l["amount"], l["balance"], l["unit"]
            dstr = t.strftime("%Y-%m-%d")
            print("%s %s %10.3f %10.3f" %(dstr, u, a, b))
        
          
    def get_date(dstr) :
        dstr = dstr.split("T")[0]
        s = dstr.split("-")
        y, m, d = int(s[0]), int(s[1]), int(s[2])
        return datetime.datetime(y, m, d)


def get_gdax(fname):
    b = gdax(fname)

def get_bitstamp(fname):
    b = bitstamp(fname)
        
def get_coinbase(fname):
    c = coinbase(fname)

def main(fname):
    if 'bitstamp' in fname:
        get_bitstamp(fname)
    elif 'coinbase' in fname:
        get_coinbase(fname)
    elif 'gdax' in fname:
        get_gdax(fname)


if __name__ == '__main__':
    main(sys.argv[1])
