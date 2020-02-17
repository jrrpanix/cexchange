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
   this example subscribes to trades on ws.bitstamp.net. </br>

```
       it uses the wsapi.hpp to specify the </br></br>
       host  = ws.bitstamp.net  (no need to specify the part wss:// as this code assumes thats the protocol) 
       port  = 443 
       subscription = {"event": "bts:subscribe", "data": {"channel": "live_trades_btcusd"}}"
       callback to recieve messages
```
```c++
      class callback : public wsapi_cb{
       public:
           void recv(const std::string &msg) {
           std::cout << msg << std::endl;
       }
```






