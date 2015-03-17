#include "request.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const rtsp::server::request& req) {
  os << req.method << " " << req.uri << " RTSP/" << req.rtsp_version_major
     << "." << req.rtsp_version_minor << "\n";
  for (const auto& h : req.headers) {
    os << h.first << ": " << h.second << "\n";
  }
  return os;
}
