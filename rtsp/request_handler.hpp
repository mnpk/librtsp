#ifndef RTSP_REQUEST_HANDLER_HPP
#define RTSP_REQUEST_HANDLER_HPP

#include <string>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace rtsp {
namespace server {

struct response;
struct request;

typedef std::map<std::string, std::function<response(const request&)>>
    resource_t;

/// The common handler for all incoming requests.
class request_handler {
 public:
  request_handler() {}
  explicit request_handler(std::vector<typename resource_t::iterator>&& rules) {
    rules_ = std::move(rules);
    for (auto r : rules) {
      std::cout << r->first << "\n";
    }
  }
  request_handler(const request_handler&) = delete;
  request_handler& operator=(const request_handler&) = delete;

  /// Handle a request and produce a response.
  void handle_request(const request& req, response& rep);

 private:
  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
  std::vector<typename resource_t::iterator> rules_;
};

}  // namespace server
}  // namespace rtsp

#endif  // RTSP_REQUEST_HANDLER_HPP
