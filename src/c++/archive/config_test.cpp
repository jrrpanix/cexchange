//
// Copyright (c) 2019 Cornelia Consulting LLC.
//
// Distributed under MIT License
//
// Official repository: https://github.com/jrrpanix/cexchange

#include "config.hpp"


int main(int argc, char **argv) {
  const char *jsonFile = argv[1];
  Config c = ConfigReader::instance().get(jsonFile, "bitstamp");
  std::cout << c.name << " " 
	    << c.host << " "
	    << c.port << " "
	    << std::endl;
  for(auto &s : c.subs)
    std::cout << s << std::endl;
}
