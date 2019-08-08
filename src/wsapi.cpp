//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
//
// Above code modified by John Reynolds, Cornelia Consulting LLC, 08/2019
// This implementation hides details and presents simple calling api

#include "wsapi.hpp"

#include "root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Report a failure
void fail(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}


// Sends a WebSocket message and prints the response
class session : public std::enable_shared_from_this<session>
{
  tcp::resolver resolver_;
  websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
  beast::flat_buffer buffer_;
  std::string host_;
  std::string text_;
  wsapi_cb *cb_;

public:
  // Resolver and socket require an io_context
  explicit session(net::io_context& ioc, ssl::context& ctx)
    : resolver_(net::make_strand(ioc))
    , ws_(net::make_strand(ioc), ctx) {
  }

  // Start the asynchronous operation
  void run(char const* host, char const* port, char const* text, wsapi_cb *cb) {
    // Save these for later
    host_ = host;
    text_ = text;
    cb_ = cb;
    
    // Look up the domain name
    resolver_.async_resolve(host, port, beast::bind_front_handler(&session::on_resolve, shared_from_this()));
  }
	
  void on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
    if(ec)
      return fail(ec, "resolve");
    
    // Set a timeout on the operation
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));
    
    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(ws_).async_connect(results,beast::bind_front_handler(&session::on_connect, shared_from_this()));
  }

  void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
    if(ec)
      return fail(ec, "connect");
    
    // Set a timeout on the operation
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

    // Perform the SSL handshake
    ws_.next_layer().async_handshake(ssl::stream_base::client,beast::bind_front_handler(&session::on_ssl_handshake,shared_from_this()));
  }

  void on_ssl_handshake(beast::error_code ec) {
    if(ec)
      return fail(ec, "ssl_handshake");
    
    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(ws_).expires_never();

    // Set suggested timeout settings for the websocket
    ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

    // Set a decorator to change the User-Agent of the handshake
    ws_.set_option(
		   websocket::stream_base::decorator(
						     [](websocket::request_type& req)
						     {
						       req.set(http::field::user_agent,
							       std::string(BOOST_BEAST_VERSION_STRING) +
							       " websocket-client-async-ssl");
						     }));
    
    // Perform the websocket handshake
    ws_.async_handshake(host_, "/", beast::bind_front_handler(&session::on_handshake, shared_from_this()));
  }
  
  void on_handshake(beast::error_code ec) {
    if(ec)
      return fail(ec, "handshake");
    ws_.async_write(net::buffer(text_),beast::bind_front_handler(&session::on_write,shared_from_this()));
  }

  void on_write(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
    if(ec)
      return fail(ec, "write");
    do_read();
  }

  void do_read() {
    ws_.async_read(buffer_, beast::bind_front_handler(&session::on_read, shared_from_this()));
  }

  void on_read(beast::error_code ec, std::size_t bytes_transferred) {
    //boost::ignore_unused(bytes_transferred);
    if(ec)
      return fail(ec, "read");
    std::stringstream strm;
    strm << beast::make_printable(buffer_.data());
    cb_->recv(strm.str());
    buffer_.consume(bytes_transferred);
    //q_->push(boost::beast::buffers_to_string(buffer_.data()));
    do_read();
  }

  void do_close() {
    ws_.async_close(websocket::close_code::normal,beast::bind_front_handler(&session::on_close,shared_from_this()));
  }
  
  void
  on_close(beast::error_code ec) {
    if(ec)
      return fail(ec, "close");
  }
};

wsapi::wsapi(const char *host, const char *port, const char *sub, wsapi_cb *cb)
  :host_(host), port_(port), sub_(sub), cb_(cb) {
}

void wsapi::start() {
  net::io_context ioc;
  
  // The SSL context is required, and holds certificates
  ssl::context ctx{ssl::context::tlsv12_client};
  
  // This holds the root certificate used for verification
  load_root_certificates(ctx);
  
  // Launch the asynchronous operation 
  std::make_shared<session>(ioc, ctx)->run(host_.c_str(), port_.c_str(), sub_.c_str(), cb_);
  
  // Run the I/O service. The call will return when
  // the socket is closed.
  ioc.run();
}
