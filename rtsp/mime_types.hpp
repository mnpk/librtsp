#ifndef RTSP_MIME_TYPES_HPP
#define RTSP_MIME_TYPES_HPP

#include <string>

namespace rtsp {
namespace server {
namespace mime_types {

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

}  // namespace mime_types
}  // namespace server
}  // namespace rtsp

#endif  // RTSP_MIME_TYPES_HPP
