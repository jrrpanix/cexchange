#pragma once
#include <string>
#include <vector>
//

////////////////////////////////////////////
// call back class to recv events from websocket
////////////////////////////////////////////
class wsapi_cb
{
public:
  virtual void recv(const std::string &) = 0;
};

////////////////////////////////////////////
// websocket api, (wrapper over beast)
////////////////////////////////////////////
class wsapi
{
public:
  /*
    host, port, subscription, simple callback class
  */
  wsapi();
  wsapi(const char *host,
	const char *port,
	const char *sub,
	wsapi_cb   *cb,
	const char *certfile="");

  wsapi(const char *host,
	const char *port,
	const std::vector<std::string> &subs,
	wsapi_cb *cb,
	const char *certfile="");

  void set_cert_file(const std::string &certfile); // ssl certificate file
  void set_host(const std::string &host);
  void set_port(const std::string &port);
  void set_subs(const std::vector<std::string> &subs);
  void set_cb(wsapi_cb *cb);
  

  // start websocket
  void start();

private:
  std::string host_;
  std::string port_;
  std::string certfile_;
  std::vector<std::string> subs_;
  wsapi_cb    *cb_;
};
