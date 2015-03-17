#ifndef RTSP_CLIENT_HPP
#define RTSP_CLIENT_HPP

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <map>
#include <boost/asio.hpp>

namespace rtsp {
namespace client {

struct response {
  std::string status_line;
  std::map<std::string, std::string> headers;
  std::string content;
};

class client {
 public:
  client(const client&) = delete;             // not copiable
  client& operator=(const client&) = delete;  // not copiable
  client(const std::string& address, uint16_t port);
  rtsp::client::response setup(const std::string& url,
                               std::map<std::string, std::string> headers);
  rtsp::client::response teardown();

 private:
  // void connect();
  // void close();
  response do_read();
  void do_write(const std::string& method, const std::string& url,
                std::map<std::string, std::string> headers = {});
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_{io_service_};
  std::string address_;
  uint16_t port_;
  std::string session_;
  std::string url_;
  uint16_t cseq_ = 0;
};

}  // namespace client
}  // namespace rtsp

std::ostream& operator<<(std::ostream& os, const rtsp::client::response& res);
#endif  // RTSP_CLIENT_HPP
