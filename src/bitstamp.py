#
# listen to trades on bitstamp via websockets
import asyncio
import websockets
import json

address = "wss://ws.bitstamp.net"

async def listener(subscription):
    async with websockets.connect(address) as websocket:
        print("connected")
        await websocket.send(json.dumps(subscription))
        while True:
            try:
                response = await websocket.recv()
                print(response)
            except:
                print("Error Found")
                quit()
                

if __name__ == '__main__':
    subscription = {"event": "bts:subscribe", "data": {"channel": "live_trades_btcusd"}}
    print("running bitstamp listener on subscription {}".format(json.dumps(subscription)))
    asyncio.get_event_loop().run_until_complete(listener(subscription))

        
