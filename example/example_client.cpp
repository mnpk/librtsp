#include "rtsp/client.hpp"

int main() {
  rtsp::client::client c("127.0.0.1", 1554);
  std::map<std::string, std::string> headers = {
      {"Require", "com.cablelabs.ermi"},
      {"Transport",
       "clab-MP2T/DVBC/UDP"
       ";multicast;bit_rate=2700000;source_address=2.2.2.2"
       ";destination=192.0.2.10;destination_port=100"
       ";multicast_address=232.1.1.1;rank=1"}};

  auto res = c.setup("rtsp://192.0.2.2/", headers);
  std::cout << res;

  res = c.teardown();
  std::cout << res;
}
