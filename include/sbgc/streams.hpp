#include <cstdint>

#ifndef __sbgc_streams__
#define __sbgc_streams__

namespace sbgc {

/**
 * Abstract, little-endian, output stream with helper methods for writing
 * inttypes.
 *
 * Whenever something is written, the head is expected to be incremented by one,
 * so that a byte is never overwritten or skipped.
 */
class OStream {
public:
  virtual void writeByte(uint8_t w) = 0;

  void writeWord(uint16_t w);

  void writeLong(uint32_t l);

  void writeFloat(float f);

  void writeString(const char *str);

  void writeBuffer(const uint8_t *buf, uint8_t size);

  void writeWordArray(uint16_t *arr, uint8_t size);

  void writeEmptyBuffer(uint8_t size);
};

/**
 * Abstract, little-endian, input stream with helper methods for writing
 * inttypes. All child classes must implement readByte().
 *
 * Whenever something is read, the head is expected to be incremented by one, so
 * that a byte is never missed or skipped.
 */
class IStream {
public:
  virtual uint8_t readByte() = 0;

  uint16_t readWord();

  uint32_t readLong();

  float readFloat();

  void readBuffer(uint8_t *buf, uint8_t size);

  void readWordArray(uint16_t *arr, uint8_t size);

  void skipBytes(uint8_t n);
};

} // namespace sbgc

#endif
