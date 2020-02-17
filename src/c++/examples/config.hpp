#pragma once

//
// Copyright (c) 2019 Cornelia Consulting LLC.
//
// Distributed under MIT License
//
// Official repository: https://github.com/jrrpanix/cexchange

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <rapidjson/document.h> 

struct Config {
  std::string name;
  std::string host;
  std::string port;
  std::vector<std::string> subs;
};

class ConfigReader {
public:

  static ConfigReader &instance() ;
  std::vector<Config> get(const char *jsonFile);
  Config get(const char *jsonFile, const char *name);

private:  
  ConfigReader();
  void parseJson(const char *jsonFile);
  
private:
  using DocumentPtr = std::shared_ptr<rapidjson::Document>;
  DocumentPtr doc_;
  std::vector<Config> configs_;
  
};
