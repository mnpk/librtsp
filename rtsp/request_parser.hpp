#ifndef RTSP_REQUEST_PARSER_HPP
#define RTSP_REQUEST_PARSER_HPP

#include <tuple>

namespace rtsp {
namespace server {

struct request;

/// Parser for incoming requests.
class request_parser {
 public:
  /// Construct ready to parse the request method.
  request_parser();

  /// Reset to initial parser state.
  void reset();

  /// Result of parse.
  enum result_type { good, bad, indeterminate };

  /// Parse some data. The enum return value is good when a complete request has
  /// been parsed, bad if the data is invalid, indeterminate when more data is
  /// required. The InputIterator return value indicates how much of the input
  /// has been consumed.
  template <typename InputIterator>
  std::tuple<result_type, InputIterator> parse(request& req,
                                               InputIterator begin,
                                               InputIterator end) {
    while (begin != end) {
      result_type result = consume(req, *begin++);
      if (result == good || result == bad)
        return std::make_tuple(result, begin);
    }
    return std::make_tuple(indeterminate, begin);
  }

 private:
  /// Handle the next character of input.
  result_type consume(request& req, char input);

  /// Check if a byte is an RTSP character.
  static bool is_char(int c);

  /// Check if a byte is an RTSP control character.
  static bool is_ctl(int c);

  /// Check if a byte is defined as an RTSP tspecial character.
  static bool is_tspecial(int c);

  /// Check if a byte is a digit.
  static bool is_digit(int c);

  /// The current state of the parser.
  enum state {
    method_start,
    method,
    uri,
    rtsp_version_r,
    rtsp_version_t,
    rtsp_version_s,
    rtsp_version_p,
    rtsp_version_slash,
    rtsp_version_major_start,
    rtsp_version_major,
    rtsp_version_minor_start,
    rtsp_version_minor,
    expecting_newline_1,
    header_line_start,
    header_lws,
    header_name,
    space_before_header_value,
    header_value,
    expecting_newline_2,
    expecting_newline_3
  } state_;
  std::string header_name_;
  std::string header_value_;
};

}  // namespace server
}  // namespace rtsp

#endif  // RTSP_REQUEST_PARSER_HPP
