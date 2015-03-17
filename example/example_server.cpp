#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "rtsp/server.hpp"
#include "rtsp/client.hpp"

using namespace rtsp::server;

int main(int argc, char* argv[]) {
  app app;

  app.route["/data/.*"] = [](const request& req) {
    // handle_data_streaming(req);
    return response::ok;
  };

  app.route["/sdv/.*"] = [](const request& req) {
    // if (req.method == "SETUP") {
    //   rtsp::client::client c("127.0.0.1", 1554);
    //   std::map<std::string, std::string> headers = {
    //       {"Require", "com.cablelabs.ermi"},
    //       {"Transport",
    //        "clab-MP2T/DVBC/UDP"
    //        ";multicast;bit_rate=2700000;source_address=2.2.2.2;destination="
    //        "192.0.2.10;destination_port=100;multicast_address=232.1.1.1;rank="
    //        "1"},
    //       {"CSeq", "0"}};
    //   auto res = c.setup("rtsp://127.0.0.1/", headers);
    // }
    return response::ok;
  };

  std::cout << "Listening on 1554...\n";
  app.port(1554).run();

  return 0;
}
