#ifndef RTSP_REQUEST_HPP
#define RTSP_REQUEST_HPP

#include <string>
// #include <vector>
#include <iostream>
#include <map>
// #include "header.hpp"

namespace rtsp {
namespace server {

/// A request received from a client.
struct request {
  std::string method;
  std::string uri;
  int rtsp_version_major;
  int rtsp_version_minor;
  // std::vector<header> headers;
  std::map<std::string, std::string> headers;
};

}  // namespace server
}  // namespace rtsp

std::ostream& operator<<(std::ostream& os, const rtsp::server::request& req);

#endif  // RTSP_REQUEST_HPP
