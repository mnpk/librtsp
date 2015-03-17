#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "rtsp/server.hpp"

using namespace rtsp::server;

int main(int argc, char* argv[]) {
  app app;

  app.route["/data/.*"] = [](const request& req) {
    // handle_data_streaming(req);
    return response::ok;
  };

  app.route["/sdv/.*"] = [](const request& req) {
    // handle_sdv(req);
    return response::ok;
  };

  std::cout << "Listening on 2554...\n";
  app.port(2554).run();

  return 0;
}
