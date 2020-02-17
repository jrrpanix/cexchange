# cexchange
access crytpo currency exchanges in C++ using websockets

* To Build and Run </br>
* uses cmake </br>
  * to build the c++ source (libs and apps) </br>
    mkdir build </br>
    cd build </br>
    cmake .. </br>
    make </br>


* 3rd Party Libraries

  * boost </br>
    bulding and installing boost</br>
    wget https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz  </br>
    tar -xzf boost_1_70_0.tar.gz </br>
    cd boost_1_70_0 </br>
    ./bootstrap.sh  # build boost build engine </br>
    ./b2            # complies boost /usr/local/lib and /usr/local/include </br>


  * These are in the include src tree
    * rapidjson </br>
      c++ header only JSON parser, fastest of ones I tested and complete from SPEC</br>
      https://github.com/Tencent/rapidjson </br>
      used for parsing market data from exchanges which are in JSON format </br>


* libs </br>
  * pthread </br>
  * libcrypto </br>
  * libssl </br>
  * librt </br>
  * boost </br>


* /src/c++/examples/simple_example.cpp </br>

```
this example subscribes to trades on ws.bitstamp.net.
it uses the wsapi.hpp to specify the
host  = ws.bitstamp.net
(no need to specify the part wss:// as this code assumes thats the protocol) 
port  = 443 
subscription = {"event": "bts:subscribe", "data": {"channel": "live_trades_btcusd"}}"
callback to recieve messages
```
```c++
 // derive a callback class from <ws/wsapi.hpp>
 // implement the recv method

 class callback : public wsapi_cb{
  public:

  void recv(const std::string &msg) {
      std::cout << msg << std::endl;
  } 
 };

int main() {
  const char *host = "ws.bitstamp.net";
  const char *port = "443";
  const char *text = "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_btcusd\"}}";

  callback cb;
  wsapi ws(host, port, text, &cb);
  ws.start();
  return 0;
}

```
```
mkdir build
cd build
cmake ..
make
./bin/simple_example

sample output
{"event":"bts:subscription_succeeded","channel":"live_trades_btcusd","data":{}}
{"data": {"microtimestamp": "1565268956596198", "amount": 0.25381784, "buy_order_id": 3919329830, "sell_order_id": 3919330463, "amount_str": "0.25381784", "price_str": "11801.15", "timestamp": "1565268956", "price": 11801.15, "type": 1, "id": 95330837}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268956812582", "amount": 1.33618216, "buy_order_id": 3919329830, "sell_order_id": 3919330485, "amount_str": "1.33618216", "price_str": "11801.15", "timestamp": "1565268956", "price": 11801.15, "type": 1, "id": 95330838}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268956923715", "amount": 0.00677966, "buy_order_id": 3919224891, "sell_order_id": 3919330485, "amount_str": "0.00677966", "price_str": "11800.00", "timestamp": "1565268956", "price": 11800.0, "type": 1, "id": 95330839}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268956986730", "amount": 1.12802033, "buy_order_id": 3919327467, "sell_order_id": 3919330485, "amount_str": "1.12802033", "price_str": "11800.00", "timestamp": "1565268956", "price": 11800.0, "type": 1, "id": 95330840}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268960656759", "amount": 0.00610024, "buy_order_id": 3919330497, "sell_order_id": 3919330626, "amount_str": "0.00610024", "price_str": "11801.17", "timestamp": "1565268960", "price": 11801.17, "type": 1, "id": 95330842}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268961048255", "amount": 0.00423119, "buy_order_id": 3919330632, "sell_order_id": 3919330667, "amount_str": "0.00423119", "price_str": "11806.02", "timestamp": "1565268961", "price": 11806.02, "type": 1, "id": 95330843}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268961342724", "amount": 0.00134182, "buy_order_id": 3919219476, "sell_order_id": 3919330719, "amount_str": "0.00134182", "price_str": "11795.00", "timestamp": "1565268961", "price": 11795.0, "type": 1, "id": 95330844}, "event": "trade", "channel": "live_trades_btcusd"}
{"data": {"microtimestamp": "1565268961407192", "amount": 9.22977042, "buy_order_id": 3919217568, "sell_order_id": 3919330719, "amount_str": "9.22977042", "price_str": "11794.07", "timestamp": "1565268961", "price": 11794.07, "type": 1, "id": 95330845}, "event": "trade", "channel": "live_trades_btcusd"}
```






