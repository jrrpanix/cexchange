//
// Copyright (c) 2019 Cornelia Consulting LLC.
//
// Distributed under MIT License
//
// Official repository: https://github.com/jrrpanix/cexchange

#include "config.hpp"
#include <fstream>
#include <rapidjson/stringbuffer.h> 
#include <rapidjson/writer.h> 

using namespace rapidjson;

template <typename T>
static std::string jsonToString(const T &t) {
  StringBuffer sb;
  Writer<StringBuffer> writer(sb);
  t.Accept(writer);
  std::string s = sb.GetString();
  return s;
}

ConfigReader::ConfigReader() :doc_(std::make_shared<Document>()){
}

ConfigReader &ConfigReader::instance() {
  static ConfigReader reader;
  return reader;
}
  
std::vector<Config> ConfigReader::get(const char *jsonFile) {
  parseJson(jsonFile);
  return configs_;
}

Config ConfigReader::get(const char *jsonFile, const char *name) {
  parseJson(jsonFile);
  for(auto &c : configs_) {
    if (c.name == name) return c;
  }
  std::string err = "no config with exchange name = " + std::string(name);
  throw  std::runtime_error(err.c_str());
}

void ConfigReader::parseJson(const char *jsonFile) {
  std::ifstream t(jsonFile);
  if (!t) {
    std::string err = "unable to open config file:" + std::string(jsonFile);
    throw std::runtime_error(err.c_str());
  }
  std::string jsonText;
  t.seekg(0, std::ios::end);   
  jsonText.reserve(t.tellg());
  t.seekg(0, std::ios::beg);
  jsonText.assign((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
  if (doc_->Parse(jsonText.c_str()).HasParseError()) {
    std::string err = "jsonError in file:" + std::string(jsonFile);
    throw std::runtime_error(err.c_str());
  }

  const Value &S = (*doc_)["active"].GetArray();
  for(int i=0; i < S.Size(); ++i) {
    configs_.push_back(Config());
    Config &config = configs_.back();
    config.name = S[i].GetString();
    const auto &xc = (*doc_)[config.name.c_str()].GetObject();
    config.host = xc["host"].GetString();
    config.port = xc["port"].GetString();
    const auto &subs = xc["subs"].GetArray();
    for(int j=0; j < subs.Size(); ++j) {
      config.subs.push_back(jsonToString<Value>(subs[j]));
    }
  }

}
