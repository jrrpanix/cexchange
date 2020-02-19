#pragma once
#include <string>
#include <vector>
//
// John Reynolds, Cornelia Consulting LLC, 08/2019
//
// Distributed under MIT License

class wsapi_cb {
public:
  virtual void recv(const std::string &) = 0;
};

class wsapi {
public:
  /*
    host, port, subscription, simple callback class
  */
  wsapi();
  wsapi(const char *host, const char *port, const char *sub, wsapi_cb *cb, const char *certfile="");
  wsapi(const char *host, const char *port, const std::vector<std::string> &subs, wsapi_cb *cb, const char *certfile="");

  /*
    example default used on linux in python3 /usr/lib/ssl/certs/653b494a.0
    this comment on beast is on the cert in root_certificates.hpp not for production
    https://github.com/boostorg/beast/issues/1702
    which is why you should set this file
  */
  void set_cert_file(const std::string &certfile); // ssl certificate file
  void set_host(const std::string &host);
  void set_port(const std::string &port);
  void set_subs(const std::vector<std::string> &subs);
  void set_cb(wsapi_cb *cb);
  
  /*
    start the websocket
  */
  void start();

private:
  std::string host_;
  std::string port_;
  std::string certfile_;
  std::vector<std::string> subs_;
  wsapi_cb    *cb_;
};
