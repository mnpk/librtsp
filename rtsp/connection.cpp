#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace rtsp {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket,
                       connection_manager& manager, request_handler& handler)
    : socket_(std::move(socket)),
      connection_manager_(manager),
      request_handler_(handler),
      session_id_(boost::uuids::to_string(boost::uuids::random_generator()())) {
}

void connection::start() { do_read(); }

void connection::stop() { socket_.close(); }

void connection::do_read() {
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
                          [this, self](boost::system::error_code ec,
                                       std::size_t bytes_transferred) {
    if (!ec) {
      request_parser::result_type result;
      request_parser request_parser;
      request req;

      std::tie(result, std::ignore) = request_parser.parse(
          req, buffer_.data(), buffer_.data() + bytes_transferred);

      if (result == request_parser::good) {
        response res;
        request_handler_.handle_request(req, res);
        res.headers["Session"] = session_id_;
        res.headers["CSeq"] = req.headers["CSeq"];
        do_write(res);
      } else if (result == request_parser::bad) {
        response res(response::bad_request);
        do_write(res);
      } else {
        do_read();
      }
    } else if (ec != boost::asio::error::operation_aborted) {
      connection_manager_.stop(shared_from_this());
    }
  });
}

void connection::do_write(response& res) {
  auto self(shared_from_this());
  boost::asio::async_write(
      socket_, res.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
          // Initiate graceful connection closure.
          // boost::system::error_code ignored_ec;
          // socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
          // ignored_ec);
          do_read();
        } else if (ec != boost::asio::error::operation_aborted) {
          connection_manager_.stop(shared_from_this());
        }
      });
}

}  // namespace server
}  // namespace rtsp
