//
// Copyright (c) 2019 Cornelia Consulting LLC.
//
// Distributed under MIT License
//
// Official repository: https://github.com/jrrpanix/cexchange

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "config.hpp"
#include "wsapi.hpp"


class MsgRecv : public wsapi_cb {
public:
  void recv(const std::string &msg) {
    std::cout << msg << std::endl;
  }
};

int main(int argc, char **argv) {
  if (argc <  3) {
    std::cerr << "usage : <jsonFile> <msgFile>" << std::endl;
    std::cerr << "genearal_listener ../server_config.json gdax" << std::endl;
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

