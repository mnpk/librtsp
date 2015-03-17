#pragma once
#include <string>
// #include <memory>
#include <stdexcept>
// #include <chrono>
#include <cstdint>
#include <vector>

class TiXmlElement;

namespace config {

struct ParseError : std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct Route {
  void Load(TiXmlElement* sub);
  std::string path;
  std::string qam_destination;
  std::string qam_name;
  std::string destination;
  std::string destination_port;
  std::string multicast_address;
};

struct SDV {
  void Load(TiXmlElement* sub);
  std::vector<Route> routes;
  std::string qam_ip = "127.0.0.1";
  uint16_t qam_port = 554;
};

SDV Load(const std::string& filepath);

}  // namespace config
