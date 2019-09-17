#include <sbgc/coms/arduino.hpp>

namespace sbgc {

/**
 * An adaptor class for the Arduino library's Stream class.
 *
 * This adds no functionality to Stream other than making it fit the ComObj
 * interface.
 */
class ArduinoComObj : public ComObj {
  /// Generic object used to communicate with serial port. This is expected to
  /// be Serial but does not have to be.
  Stream *serial;

public:
  ArduinoComObj(Stream *s) { serial = s; }

  virtual uint16_t getBytesAvailable() { return serial->available(); }

  virtual uint8_t readByte() { return serial->read(); }

  virtual void writeByte(uint8_t b) { serial->write(b); }
};

} // namespace sbgc