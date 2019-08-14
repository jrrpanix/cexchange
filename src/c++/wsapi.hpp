#pragma once
#include <string>
#include <vector>
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
  wsapi(const char *host, const char *port, const std::vector<std::string> &subs, wsapi_cb *cb);
  void start();

private:
  std::string host_;
  std::string port_;
  std::vector<std::string> subs_;
  wsapi_cb    *cb_;
};
