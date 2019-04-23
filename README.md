# SimpleBGC Serial API

A fork of the official [SimpleBGC Serial
API](https://github.com/alexmos/sbgc-api-examples) written by Aleksei
Moskalenko with improved documentation, high-level usage, unit tests, and more.

The specification of the API that this project implements are available
[here](http://www.basecamelectronics.com/serialapi/).

This fork was started when NC State's Aerial Robotic Club bought a SimpleBGC
gimbal controller and was dissatisfied with the documentation and maintenance
of provided library. Because of this, we have forked the API examples repo,
isolated the libraries, improved the documentation, and made other
modifications.

This fork will attempt to stay up to date with the [official serial
API](http://www.basecamelectronics.com/serialapi/) but will not be actively
watching it for updates and changes.

## Design

Broadly, there are two ways you can use this API: a low-level and a high-level.

The **low-level** is written in C++ and is only meant to be accessed through
C++. It contains a simple *serial command data type*; a *parser*, which
translates back and forth between the serial command data type and a series of
bytes; and an *abstract com object* that can read and write to the serial port.

The **high-level** is written in C++ with the intent of being used in other
languages. It essentially wraps the low-level by providing a limited interface
for performing standard operations through a given com object. This is included
so that the user never has to worry about the specifics of how to communicate
with gimbal and instead can think about sending and receiving commands.

## Notes

* The `ArduinoComObj` has never been tested by any maintainers of this repo,
  but is taken from upstream.
