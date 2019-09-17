/**
 * Core parts used to implement the SBGC serial API.
 */

#ifndef __sbgc_core__
#define __sbgc_core__

// For int types
#include <cstdint>
#include <sbgc/streams.hpp>

namespace sbgc {

extern const int MAX_STRING_LENGTH;

extern const int MAX_PACKET_SIZE;

/**
 * Abstract representation of a command defined by the serial API. According to
 * the serial API, every command has an ID and a series of bytes as arguments.
 */
class SerialCommand : public OStream {
  uint8_t writeHead;
  uint8_t readHead;

protected:
  // Inherit constants
  const uint8_t PAYLOAD_SIZE;
  uint8_t payload[PAYLOAD_SIZE];
  SerialCommand(const uint8_t size) : PAYLOAD_SIZE(size) {}

public:
  virtual uint8_t getVersion() = 0;

  virtual uint8_t getCommandId() = 0;

  virtual void getPayload(*uint8_t payloadStorage) = 0;

  virtual uint8_t getPayloadSize() = 0;

  /**
   * Serialize a serial command struct, using protocol version 1, and write it
   * to the com object.
   * @param cmd The SerialCommand struct to serialize and write.
   * @param com The ComObj to write the serialized command to.
   */
  virtual uint8_t writeCommand(ComObj &com) = 0;

  /**
   * Read a single data packet from the com object and deserialize it, using
   * protocol version 1, into serial command struct.
   * @param cmd The SerialCommand struct to put the deserialized command into.
   * @param com The ComObj to read the serialized command from.
   * @return On success, 0. On failure, -1.
   */
  virtual uint8_t readCommand(const ComObj &com) = 0;
};

/**
 * Interface defining how to interact with communications port.
 *
 * The implementation of this is hardware specific and should be thoroughly
 * tested to assure that it follows the criteria set out here.
 */
class ComObj : public OStream, public IStream {
public:
  virtual uint16_t getBytesAvailable() const = 0;
};

/**
 * Read single data packet from com object and deserialize it.
 * @param cmd SerialCommand to contain deserialized command.
 * @param com ComObj to read serialized command from.
 * @return On success, 0. On failure, -1.
 */
int readCommand(SerialCommand &cmd, ComObj &com);

/**
 * Serialize SerialCommand struct and write to ComObject.
 * @param cmd SerialCommand to serialize and write.
 * @param com ComObj to write serialized command to.
 */
void writeCommand(SerialCommand &cmd, ComObj &com);

} // namespace sbgc

#endif
