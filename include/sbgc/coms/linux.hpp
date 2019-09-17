/**
Reference implementation of sbgc::ComObj, using file descriptors, for Linux
machines.
*/

#include <sbgc/core.hpp>

#ifndef __linux__
#define __linux__

namespace sbgc {

/**
 * A com object for interacting with Linux serial ports and generic TTYs.
 */
class LinuxComObj : public ComObj {
public:
  /**
   * Opens and locks the given serial port / TTY using a file descriptor.
   *
   * @param incoming_portname String defining the path to the file descriptor to
   * open.
   */
  LinuxComObj(std::string incoming_portname);

  /**
   * @return The file descriptor for the serial port.
   */
  int getFileDescriptor();

  /**
   * @return The portname/filename for the serial port.
   */
  std::string getPortName();
};

} // namespace sbgc

#endif