#ifndef RTSP_REPLY_HPP
#define RTSP_REPLY_HPP

#include <string>
#include <vector>
#include <map>
#include <boost/asio.hpp>
// #include "header.hpp"

namespace rtsp {
namespace server {

/// A response to be sent to a client.
struct response {
  /// The status of the response.
  enum status_type {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  } status;

  /// The headers to be included in the response.
  // std::vector<header> headers;
  std::map<std::string, std::string> headers;

  /// The content to be sent in the response.
  std::string content;

  /// Convert the response into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the response object must remain valid
  /// and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> to_buffers();

  /// Get a stock response.
  // static response stock_response(status_type status);
  response(status_type status);
  response() {}
};

}  // namespace server
}  // namespace rtsp

#endif  // RTSP_REPLY_HPP
