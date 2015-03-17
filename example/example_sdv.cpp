#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "rtsp/server.hpp"
#include "rtsp/client.hpp"
#include "config/config.hpp"

using namespace rtsp::server;

int main(int argc, char* argv[]) {
  app app;

  // load configured routes
  config::SDV config = config::Load("sdv.xml");
  for (auto& r : config.routes) {
    app.route[r.path] = [&r, &config](const request& req) {
      if (req.method == "SETUP") {
        std::string transport =
            "clab-MP2T/DVBC/QAM;qam_name=" + r.qam_name + ";qam_destination=" +
            r.qam_destination +
            ",clab-MP2T/DVBC/"
            "UDP;multicast;bit_rate=2700000;source_address=2.2.2.2;"
            "destination=" +
            r.destination + ";destination_port=" + r.destination_port +
            ";multicast_address=" + r.multicast_address + ";rank=1";

        std::map<std::string, std::string> headers = {
            {"Require", "com.cablelabs.ermi"}, {"Transport", transport}};


        rtsp::client::client c(config.qam_ip, config.qam_port);
        auto res = c.setup("rtsp://"+config.qam_ip+"/sdv/", headers);
        std::cout << res;
      }

      return response::ok;
    };
  }

  std::cout << "Listening on 1554...\n";
  app.port(1554).run();

  return 0;
}
