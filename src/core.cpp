#include <sbgc/core.hpp>
// Throwing exceptions
#include <cstring>
#include <stdexcept>

namespace sbgc {

/// Maximum number of characters in an SBGC Serial API specification string.
const int MAX_STRING_LENGTH = 255;

/// Maximum number of bytes for a serial command packet. This is used for
/// allocation of arrays.
const int MAX_PACKET_SIZE = 255;

// Optimized skips
SerialCommand::writeEmptyBuffer(uint8_t size) {
  writeHead += size;
}

SerialCommand::skipBytes(uint8_t n) {
  readHead += n;
}

SerialCommand::writeByte(uint8_t b) {
  if (byteHead > PAYLOAD_SIZE) {
    raise std::runtime_error("SerialCommand payload out of space");
  }
  payload[writeHead++] = b;
}

} // namespace sbgc
