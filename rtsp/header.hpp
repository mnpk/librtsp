#ifndef RTSP_HEADER_HPP
#define RTSP_HEADER_HPP

#include <string>

namespace rtsp {
namespace server {

struct header {
  std::string name;
  std::string value;
};

}  // namespace server
}  // namespace rtsp

#endif  // RTSP_HEADER_HPP
