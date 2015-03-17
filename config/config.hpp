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
  std::string destination;
  std::string destination_port;
  std::string multicast_address;
};

struct SDV {
  void Load(TiXmlElement* sub);
  std::vector<Route> routes_;
};

SDV Load(const std::string& filepath);

}  // namespace config
