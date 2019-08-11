#include "wsapi.hpp"
#include <iostream>
#include <vector>

//
// subscribe to trades on bitstamp for btcusd, ethusd, ltcusd, xrpusd, bchusd
// create callback class derived from wsapi_cb
// print messages to std::cout

class callback : public wsapi_cb{
public:
  void recv(const std::string &msg) {
    std::cout << msg << std::endl;
  }
};


int main() {
  const char *host = "ws.bitstamp.net";
  const char *port = "443";
  std::vector<std::string> subs = {"{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_btcusd\"}}",
				   "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_ethusd\"}}",
				   "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_ltcusd\"}}",
				   "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_xrpusd\"}}",
				   "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_bchusd\"}}"};

  callback cb;
  wsapi ws(host, port, subs, &cb);
  ws.start();
  return 0;
}

