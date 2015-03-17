#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "mime_types.hpp"
#include "response.hpp"
#include "request.hpp"

namespace rtsp {
namespace server {

void request_handler::handle_request(const request& req, response& res) {
  // Decode url to path.
  std::string uri;
  if (!url_decode(req.uri, uri)) {
    res = response(response::bad_request);
    return;
  }

  std::string protocol = "rtsp://";
  size_t pos_protocol = uri.find(protocol);
  if (pos_protocol != std::string::npos) {
    uri = uri.substr(pos_protocol + protocol.length());
    uri = uri.substr(uri.find_first_of("/"));
  }

  std::cout << "[receive request]\n";
  std::cout << req << "\n";

  for (auto r : rules_) {
    std::regex e(r->first);
    std::smatch sm_res;
    if (std::regex_match(uri, sm_res, e)) {
      std::cout << "rule matched!\n";
      res = r->second(req);
      return;
    }
  }
  res = response(response::ok);
  return;

  // // Request path must be absolute and not contain "..".
  // if (uri.empty() || uri[0] != '/' ||
  //     uri.find("..") != std::string::npos) {
  //   res = response::stock_response(response::bad_request);
  //   return;
  // }
  //
  // // If path ends in slash (i.e. is a directory) then add "index.html".
  // if (uri[uri.size() - 1] == '/') {
  //   uri += "index.html";
  // }
  //
  // // Determine the file extension.
  // std::size_t last_slash_pos = uri.find_last_of("/");
  // std::size_t last_dot_pos = uri.find_last_of(".");
  // std::string extension;
  // if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
  //   extension = uri.substr(last_dot_pos + 1);
  // }
  //
  // // Open the file to send back.
  // std::string full_path = doc_root_ + uri;
  // std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  // if (!is) {
  //   res = response::stock_response(response::not_found);
  //   return;
  // }

  // Fill out the response to be sent to the client.
  //
  // res.status = response::ok;
  // char buf[512];
  // while (is.read(buf, sizeof(buf)).gcount() > 0)
  //   res.content.append(buf, is.gcount());
  // res.headers.resize(2);
  // res.headers[0].name = "Content-Length";
  // res.headers[0].value = std::to_string(res.content.size());
  // res.headers[1].name = "Content-Type";
  // res.headers[1].value = mime_types::extension_to_type(extension);
}

bool request_handler::url_decode(const std::string& in, std::string& out) {
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i) {
    if (in[i] == '%') {
      if (i + 3 <= in.size()) {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value) {
          out += static_cast<char>(value);
          i += 2;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else if (in[i] == '+') {
      out += ' ';
    } else {
      out += in[i];
    }
  }
  return true;
}

}  // namespace server
}  // namespace rtsp
