# cexchange - C++ for Crypto Currency Market Data
__Crytpo Currency exchange access in C++ using websockets__

* __About__
  * this git provides an extremely simple api wrapper class to make it easy write c++ websocket code </br>
  * by providing a wrapper around  boost/beast websockets </br>
  * the objective is to get up and running rapidly in c++ </br>
  * websocket api </br>
    * https://github.com/jrrpanix/cexchange/tree/master/src/c++/ws/wsapi.hpp </br>
  * sample json config file </br>
    * https://github.com/jrrpanix/cexchange/tree/master/config/server_config.json </br>
  * simple example </br>
    * https://github.com/jrrpanix/cexchange/tree/master/src/c++/examples/simple_example.cpp </br>
  * general example </br>
    * the quickest most general way to get going </br>
    * put then exchange subscription in json following format in server_config.json </br>
    * https://github.com/jrrpanix/cexchange/tree/master/src/c++/examples/general_listener.cpp </br>
  * websocket api wraps boost/beast websockets instructions below on getting and building boost </br>
  * json is parsed using c++ project rapidjson </br>
    * https://github.com/Tencent/rapidjson </br>
  * websocket libs also require libcrypto, libssl </br>

* __To Build and Run__ </br>
```
    mkdir build
    cd build
    cmake ..
    make
    # running executables
    ./bin/simple_example
    ./bin/general_listener ../config/server_config.json gdax 
    ./bin/general_listener ../config/server_config.json bitstamp
    ./bin/general_listener ../config/server_config.json kraken
```

* __SSL Certificates__ </br>
```
   # the example code comes with a file called root_certificates.hpp

   # refer to this thread on them not being for production
   # https://github.com/boostorg/beast/issues/1702

   # the example code defaults to them but its not recommeded for prod

   # on linux ssl certificates can be found here:
   # /usr/lib/ssl/certs/ and /usr/share/ca-certificates/
   # python3 will load this one on websockets
   # /usr/lib/ssl/certs/Baltimore_CyberTrust_Root.pem -> /usr/share/ca-certificates/mozilla/Baltimore_CyberTrust_Root.crt
   # /usr/lib/ssl/certs/653b494a.0 -> Baltimore_CyberTrust_Root.pem
   # /usr/lib/ssl/certs/653b494a.0

   # also note on the SSL handsake this error was occurring on coinbasepro websockets
   #
   #     ssl_handshake: sslv3 alert handshake failure
   #
   # it was fixed by the following lines of code (refer to issue 1702)

   if(! SSL_set_tlsext_host_name(ws_.next_layer().native_handle(), host_.c_str())) {
     std::cerr << "SSL_set_tlsext_host_name: error " << std::endl;
     return;
  }

```


* __Exchange json configurations in server_config.json__</br>
* the executable __general_listener__ designed for using each exchanges json config</br>
  * __kraken__ </br>
    ```
     ./bin/general_listener ../config/server_config.json kraken
    ```
  * __bitstamp__ </br>
    ```
    ./bin/general_listener ../config/server_config.json bitstamp
    ``` 
  * __coinbasepro__ (formely know as gdax) </br>
    ```
    ./bin/general_listener ../config/server_config.json gdax
    ```
  * __consult each exchange for different/advanced subscription options__ </br>

* __3rd Party Libraries__

  * __boost__ </br>
  ```
    # bulding and installing boost
    # latest release as of 2/19/2020
    wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz
    tar -xzf boost_1_72_0.tar.gz
    cd boost_1_72_0 </br>
    ./bootstrap.sh     # build boost build engine
    ./b2               # complies boost 
    sudo ./b2 install  # /usr/local/lib and /usr/local/include
   ```

  * These are in the include src tree
    * __rapidjson__ </br>
      c++ header only JSON parser, fastest of ones I tested and complete from SPEC</br>
      https://github.com/Tencent/rapidjson </br>
      used for parsing market data from exchanges which are in JSON format </br>


* __libs__ </br>
  * pthread </br>
  * libcrypto </br>
  * libssl </br>
  * librt </br>
  * boost </br>


* /src/c++/examples/simple_example.cpp </br>

```
This example subscribes to trades on ws.bitstamp.net. It uses the wsapi.hpp to specify the
host (ws.bitstamp.net) and port (443). NOTE not necessary to specify wss://ws.bitstamp.net.


host  = ws.bitstamp.net
port  = 443 
subscription = {"event": "bts:subscribe", "data": {"channel": "live_trades_btcusd"}}"

```
```c++
#include <ws/wsapi.hpp>
#include <iostream>

/**
 subscribe to trades on bitstamp for btcusd
 create callback class derived from wsapi_cb
 print messages to std::cout
**/

 // derive a callback class from <ws/wsapi.hpp>
 class callback : public wsapi_cb{
  public:

  // implement the recv method
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






