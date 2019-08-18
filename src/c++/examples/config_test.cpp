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
