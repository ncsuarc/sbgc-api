/**
Reference implementation of sbgc::ComObj for Arduinos.

WARNING: It is strongly recommended to increase the serial buffer size to 150
bytes or more in the Arduino IDE, since the default buffer of 64 bytes is not
large enough to fit some incomining commands.
*/

#include <sbgc/core.hpp>

#ifndef __sbgc_coms_arduino__
#define __sbgc_coms_arduino__

namespace sbgc {

/**
 * A com object for Arduinos to interact with serial ports.
 */
class ArduinoComObj : public ComObj {
public:
  /**
   * Create a ArduinoComObj using the generic Stream to interact with the serial port.
   */
  ArduinoComObj(Stream *s);
};

} // namespace sbgc

#endif