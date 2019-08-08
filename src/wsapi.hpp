#pragma once
#include <string>

//
// John Reynolds, Cornelia Consulting LLC, 08/2019
//

class wsapi_cb {
public:
  virtual void recv(const std::string &) = 0;
};

class wsapi {
public:
  /*
    host, port, subscription, simple callback class
  */
  wsapi(const char *host, const char *port, const char *sub, wsapi_cb *cb);
  void start();

private:
  std::string host_;
  std::string port_;
  std::string sub_;
  wsapi_cb    *cb_;
};
