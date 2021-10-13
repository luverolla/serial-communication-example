# Serial communication example with ChibiOS on STM32 and Java Server

This shows a simple example of serial communication between
* ChibiOS-based firmware running on STM32 ARM MCU (the client)
* Simple Java SE application (thr server)

The client gets data from an ultrasonic distance sensor, and transmit to a virtual serial port.

The example is made on a Windows system, with a coordinated baudrate of 38400 bps, and via the COM7 virtual serial port.
If you want to replicate the example on different enviroments, change baudrate and port number accordingly.

This repository is under MIT license.
