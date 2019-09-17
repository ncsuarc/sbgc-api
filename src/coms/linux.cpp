#include <sbgc/coms/linux.hpp>

/**
 * BUH
 *
 * This works using low level file descriptors for serial ports / TTYs and
 * setting their proper settings so that we can read and write bytewise.
 */
class LinuxComObj : public ComObj {
private:
  /// File descriptor of serial port.
  int fd;
  /// File name of serial port.
  std::string portname;

public:
  /**
   * Opens a file descriptor for the given filename and sets it up as a
   * serial port.
   *
   * @param incoming_portname The C string defining the path to the file
   * descriptor to open.
   * @todo Make this lock the terminal too. This currently isn't done to
   * prevent locking ourselves out.
   */
  LinuxComObj(std::string incoming_portname) {
    // Open serial port
    portname = incoming_portname;
    fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
      throw std::invalid_argument(strerror(errno));
    }

    // Open serial port termios
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
      throw std::runtime_error(strerror(errno));
    }

    // Set baud rate
    cfsetspeed(&tty, BAUD_RATE);

    // Set up non-canonical mode (not line-based)
    tty.c_iflag &=
        ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    // We never block on read
    tty.c_cc[VMIN] = 0;
    // We wait for at least TIMEOUT_MS to get some data
    tty.c_cc[VTIME] = TIMEOUT_MS / 100;

    // 8-bit chars (bytes)
    tty.c_cflag |= CS8;
    // shut off xon/xoff ctrl
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cflag |= CLOCAL;             // ignore modem controls,
    tty.c_cflag |= CREAD;              // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
      throw std::runtime_error(strerror(errno));
    }

    // Lock the terminal
    // When we do this for real, we should create a lock and unlock method
    // ioctl(fd, TIOCEXCL);
  }

  /**
   * Find number of bytes available on serial port.
   *
   * This first calls select() on the port, to assure that the port is ready for
   * reading. Then, it calls FIONREAD with ioctl on the port to get the number
   * of bytes available.
   *
   * @return The number of bytes available to read from the serial port.
   * @exception std::runtime_error When there is an issue getting the number
   * of bytes from the Gimbal's fd (serial port).
   */
  virtual uint16_t getBytesAvailable() {
    // We watch our serial file descriptor as a reading file descriptor.
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    struct timeval tv;
    tv.tv_sec = TIMEOUT_MS / 1000;
    tv.tv_usec = (TIMEOUT_MS * 1000) % 1000000;

    int retval = select(fd + 1, &rfds, NULL, NULL, &tv);
    if (retval == -1) {
      throw std::runtime_error(strerror(errno));

    } else if (retval == 0) {
      // No bytes available after 200 ms
      return 0;
    }

    // Now we get the number of bytes available
    uint16_t avaiable;
    if (ioctl(fd, FIONREAD, &avaiable) != 0) {
      throw std::runtime_error(strerror(errno));
    }
    return avaiable;
  }

  /**
   * @return A single byte to read from the com.
   */
  virtual uint8_t readByte() {
    uint8_t b;
    read(fd, &b, 1);
    return b;
  }

  /**
   * @param b A single byte to write to the com.
   */
  virtual void writeByte(uint8_t b) { write(fd, &b, 1); }

  /**
   * @return The file descriptor for the serial port.
   */
  int getFileDescriptor() { return fd; }

  /**
   * @return The portname/filename for the serial port.
   */
  std::string getPortName() { return portname; }
}