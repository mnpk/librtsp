#ifndef RTSP_SERVER_HPP
#define RTSP_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace rtsp {
namespace server {

typedef std::map<std::string, std::function<response(const request&)>>
    resource_t;

/// The top-level class of the RTSP server.
class server {
 public:
  server(const server&) = delete;
  server& operator=(const server&) = delete;

  /// Construct the server to listen on the specified TCP address and port,
  /// and
  /// serve up files from the given directory.
  explicit server(const std::string& address, const std::string& port,
                  std::vector<typename resource_t::iterator>&& rules);

  /// Run the server's io_service loop.
  void run();

 private:
  /// Perform an asynchronous accept operation.
  void do_accept();

  /// Wait for a request to stop the server.
  void do_await_stop();

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// The signal_set is used to register for process termination
  /// notifications.
  boost::asio::signal_set signals_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The connection manager which owns all live connections.
  connection_manager connection_manager_;

  /// The next socket to be accepted.
  boost::asio::ip::tcp::socket socket_;

  /// The handler for all incoming requests.
  request_handler request_handler_;
};

struct app {
  app& port(uint16_t p) {
    pn = p;
    return *this;
  }

  void run() {
    std::vector<typename resource_t::iterator> rules;
    rules.clear();
    for (auto r = route.begin(); r != route.end(); ++r) {
      std::cout << "route " << r->first << std::endl;
      rules.push_back(r);
    }

    s.reset(new server("0.0.0.0", std::to_string(pn), std::move(rules)));
    s->run();
  }

  resource_t route;
  std::unique_ptr<server> s;
  uint16_t pn = 8000;
};

}  // namespace server
}  // namespace rtsp

#endif  // RTSP_SERVER_HPP
