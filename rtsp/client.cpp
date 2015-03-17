#include "client.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace rtsp {
namespace client {

using boost::asio::ip::tcp;

client::client(const std::string& address, uint16_t port)
    : address_(address), port_(port) {
  // Get a list of endpoints corresponding to the server name.
  tcp::resolver resolver(io_service_);
  tcp::resolver::query query(address_, std::to_string(port_));
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
  tcp::resolver::iterator end;

  // Try each endpoint until we successfully establish a connection.
  boost::system::error_code error = boost::asio::error::host_not_found;
  while (error && endpoint_iterator != end) {
    socket_.close();
    socket_.connect(*endpoint_iterator++, error);
  }
  if (error) throw boost::system::system_error(error);
}

rtsp::client::response client::setup(
    const std::string& url, std::map<std::string, std::string> headers) {
  url_ = url;
  do_write("SETUP", url, headers);
  return do_read();
}

rtsp::client::response client::teardown() {
  do_write("TEARDOWN", url_);
  return do_read();
}

void client::do_write(const std::string& method, const std::string& url,
                      std::map<std::string, std::string> headers) {
  boost::asio::streambuf request;
  std::ostream request_stream(&request);

  request_stream << method << " " << url << " RTSP/1.0\r\n";
  for (auto& h : headers) {
    request_stream << h.first << ": " << h.second << "\r\n";
  }
  if (false == session_.empty()) {
    request_stream << "Session: " << session_ << "\r\n";
  }
  request_stream << "CSeq: " << cseq_++ << "\r\n";
  request_stream << "\r\n";

  // Send the request.
  // std::cout << "sending request...\n" << &request << "\n";
  boost::asio::write(socket_, request);
}

response client::do_read() {
  response res;
  boost::asio::streambuf buf;
  boost::asio::read_until(socket_, buf, "\r\n");

  // Check that buf is OK.
  std::istream response_stream(&buf);
  std::string rtsp_version;
  response_stream >> rtsp_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;

  std::getline(response_stream, status_message);
  std::stringstream ss;
  ss << rtsp_version << " " << status_code << status_message;
  res.status_line = ss.str();
  if (!response_stream || rtsp_version.substr(0, 5) != "RTSP/") {
    std::cout << "Invalid buf\n";
    throw std::runtime_error("invalid buf");
  }

  // Read the buf headers, which are terminated by a blank line.
  boost::asio::read_until(socket_, buf, "\r\n\r\n");

  // Process the buf headers.
  std::string header;
  int content_length = 0;
  while (std::getline(response_stream, header) && header != "\r") {
    std::string name = header.substr(0, header.find(":"));
    std::string value = header.substr(header.find(":") + 1);
    value = value.substr(0, value.find("\r"));
    boost::algorithm::trim(value);

    if (name == "Content-Length") content_length = std::stoi(value);
    if (name == "Session") session_ = value;
    res.headers[name] = value;
  }

  // Write whatever content we already have to output.
  std::stringstream ss_content;
  ss_content << &buf;
  if (buf.size() > 0) ss_content << &buf;
  content_length -= buf.size();

  if (content_length > 0) {
    // Read until EOF, writing data to output as we go.
    boost::system::error_code error = boost::asio::error::host_not_found;
    boost::asio::read(socket_, buf,
                      boost::asio::transfer_exactly(content_length), error);
    ss_content << &buf;
  }

  res.content = ss_content.str();
  return res;
}

}  // namespace client
}  // namespace rtsp

std::ostream& operator<<(std::ostream& os, const rtsp::client::response& res) {
  os << res.status_line << "\n";
  for (auto& h : res.headers) {
    os << h.first << ": " << h.second << "\n";
  }
  os << res.content << "\n";
  return os;
}
