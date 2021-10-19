#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "config.hpp"
#include <ws/wsapi.hpp>


class MsgRecv : public wsapi_cb {
public:
  void recv(const std::string &msg) {
    std::cout << msg << std::endl;
  }
};


/**
   subscribe to market data from a json configuration file
**/
int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage:" << argv[0] << " <json_config> <exchange" << std::endl;
    std::cerr << "example:" << argv[0] << "../config/server_config.json gdax" << std::endl;
    return 1;
  }
  int cnt = 1;
  const char *jsonFile = argv[cnt++];
  const char *name = argv[cnt++];
  Config c = ConfigReader::instance().get(jsonFile, name);
  MsgRecv recv;
  wsapi ws(c.host.c_str(), c.port.c_str(), c.subs, &recv);
  ws.start();
  return 0;
}

