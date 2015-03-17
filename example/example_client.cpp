#include "rtsp/client.hpp"

int main() {
  rtsp::client::client c("127.0.0.1", 1554);
  std::map<std::string, std::string> headers = {
    {"Require", "com.cablelabs.ermi"},
    {"Transport",
     "clab-MP2T/QAM;unicast;"
     "x-external-cellid-upper=200;x-external-cellid-lower=100;x-service-group-"
     "id=100;x-service-priority-id=5;x-service-priority-criteria-id=3;x-"
     "candidate-tsids=2000,2001;x-clientid=333"}};
     auto res = c.setup("rtsp://127.0.0.1/sdv/1.mpg", headers);
  std::cout << res;

  res = c.teardown();
  std::cout << res;
}
