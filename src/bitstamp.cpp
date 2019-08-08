#include "wsapi.hpp"
#include <iostream>

//
// subscribe to trades on bitstamp for btcusd
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
  const char *text = "{\"event\": \"bts:subscribe\", \"data\": {\"channel\": \"live_trades_btcusd\"}}";

  callback cb;
  wsapi ws(host, port, text, &cb);
  ws.start();
  return 0;
}

