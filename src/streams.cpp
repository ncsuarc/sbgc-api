#include <sbgc/streams.hpp>

namespace sbgc {

/**
 * Write 16-bit integer as 2 little-endian bytes.
 * @param w 16-bit integer to write.
 */
void OStream::writeWord(uint16_t w) {
  writeByte(w);      // low
  writeByte(w >> 8); // high
}

/**
 * Write 32-bit integer as 4 little-endian bytes (2 little endian words).
 * @param w 32-bit integer to write.
 */
void OStream::writeLong(uint32_t l) {
  writeWord(l);       // low
  writeWord(l >> 16); // high
}

/**
 * Write IE 754 encoded floating point number as array of bytes.
 * @param f Single-precision floating point number to write.
 */
void OStream::writeFloat(float f) { writeBuf(&f, sizeof(float)); }

/**
 * Write C string as SBGC Serial API specification string. SBGC strings
 * are non-null-terminated ASCII arrays preceded by a single byte specifying
 * the length of the string. As such, SBGC strings have a maximum length of
 * MAX_STRING_LENGTH.
 * @param str C string to write.
 */
void OStream::writeString(const char *str) {
  uint8_t len = strlen(str);
  if (len > MAX_STRING_LENGTH) {
    throw std::runtime_error("Cannot write string: Exceeds max length");
  }
  writeByte(len);
  writeBuffer((uint8_t *)str, len);
}

/**
 * Write array of bytes of given length.
 * @param buf Array of bytes to write.
 * @param size Number of bytes in array to write. If this is larger than the
 * length of buf, garbage data is written.
 */
void OStream::writeBuffer(const uint8_t *buf, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    writeByte(buf[i]);
  }
}

/**
 * Write array of words of given length.
 * @param arr Array of words to write.
 * @param size Number of bytes in array to write. If this is larger than the
 * length of buf, garbage data is written.
 */
void OStream::writeWordArray(uint16_t *arr, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    writeWord(arr[i]);
  }
}

/**
 * Write empty bytes.
 * @param size Number of empty bytes to write.
 */
void OStream::writeEmptyBuffer(uint8_t size) {
  while (size-- > 0) {
    writeByte(0);
  }
}

/**
 * Read 16-bit integer as 2 little-endian bytes.
 * @return 16-bit integer.
 */
uint16_t IStream::readWord() {
  // low + high
  return (uint16_t)readByte() + ((uint16_t)readByte() << 8);
}

/**
 * Read 32-bit integer as 4 little-endian bytes (2 little endian words).
 * @return 32-bit integer.
 */
uint32_t IStream::readLong() {
  // low + high
  return (uint32_t)readWord() + ((uint32_t)readWord() << 16);
}

/**
 * Read IE 754 encoded floating point number.
 * @return Single-precision floating point number read.
 */
float IStream::readFloat() {
  float f;
  readBuffer((uint8_t *)&f, sizeof(float));
  return f;
}

/**
 * Read array of bytes of given length.
 * @param buf Array of bytes to write.
 * @param size Number of bytes in array to write. If this is larger than the
 * length of buf, garbage data is written.
 */
void IStream::readBuffer(uint8_t *buf, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    buf[i] = readByte();
  }
}

/**
 * Read array of words of given length.
 * @param arr Array of words to write.
 * @param size Number of bytes in array to write. If this is larger than the
 * length of buf, garbage data is written.
 */
void IStream::readWordArray(uint16_t *arr, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    arr[i] = readWord();
  }
}

/**
 * Skip bytes, throwing away their data.
 * @param size Number of empty bytes to write.
 */
void IStream::skipBytes(uint8_t size) {
  while (size-- > 0) {
    readByte();
  }
}

} // namespace sbgc
