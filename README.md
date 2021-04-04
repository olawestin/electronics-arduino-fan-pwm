# PWM fan controller

An Arduino based PWM fan controller that is controlled through the USB serial port.

The fan controller program reads characters that are sent to the serial port and reacts to characters between '0' (0% fan PWM level) and '9' (100% fan PWM level). The PWM level controls the speed of a fan.

This example uses a [PWM library by Sam Knight](https://forum.arduino.cc/index.php?topic=117425.0).

## Theory

The pins of a 4-pin computer fan are as follows:

* Black - Ground
* Yellow - +12V (the fan might also work with lower voltages)
* Green - Tachometer, one pulse per full rotation of the fan
* Blue - Control

The control pin uses a 25 kHz [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) signal. In short the controller sends a square wave with 25000 pulses every second. The amount of time that the signal is high during each pulse determines the speed that the fan should run at.

The Arduino board has built in timers that allows it to generate such a signal in an easy way.

## Prerequisites

You need:

* An Arduino board. Most board types should work, but for this example I will assume that you have an Arduino Uno or similar board.
* A 12V PWM controllable fan. Most standard 3 or 4 pin computer fans should work.
* A 12V power supply. Make sure that the connector matches in size and polarity with the Arduino power connector (5.5 mm, center positive). A typical computer fan draws well below 1A so any power supply that can provide at least 1A should be fine. Look for markings similar to this: ![12V DC symbols](Power-12VDC-1A-positive-center.png)
* Connector wires. Use male-male connectors for connecting the Arduino to either the fan connector or to a breadboard.
* A USB cable.

Optionally:

* A breadboard.
* A 4-pin fan header (4-pin Molex KK 47053-1000).

## Wiring

You can connect the fan directly to the Arduino board. This works fine but the connector wires might not fit the fan connector perfectly. You may want to stablilize the connection with some electrical insulation tape.

![Wiring directly](fan-pwm-basic_bb.svg)

If you have a fan header you can place it on a breadboard and connect that to the Arduino instead.

![Wiring via a breadboard](fan-pwm-breadboard_bb.svg)

## Software

* Install the [Arduino IDE](https://www.arduino.cc/en/software).

* Install the PWM library
  * Download the latest version from <http://code.google.com/p/arduino-pwm-frequency-library/downloads/list>.
  * Unzip the downloaded file.
  * Copy the PWM subdirectory into the _libraries_ directory in the Arduino user sketchbook location.
    * To find or set the user sktechbook location, open the menu _File - Preferences_ in the Arduino IDE.
    * On Windows this will by default be `%HOMEPATH%\Documents\Arduino`.

## Setup

* Connect the Arduino board to your computer using a USB cable.
* Connect the 12V power supply to the Arduino board.
  * If you only have the USB cable connected the fan will be powered by 5V resulting in a lower speed.
  * Note that the connected fan will start turning as soon as you connect either a USB cable or the power supply.
* Open the [fan-pwm.ino](fan-pwm.ino) sketch.
* Select your model of Arduino board using the menu item _Tools - Board_.
* Compile and upload the program by pressing the Upload button or the menu item _Sketch - Upload_.

## Control

* Select the correct serial port using the menu item _Tools - Port_. It might not always be obvious which port to use so you may have to try those that are available until you find the right one.
* Open the serial monitor by pressing the Serial Monitor button or the menu item _Tools - Serial Monitor_.
* Select the same baud rate as is set up in the code. In this case it should be 9600.
* To control the fan speed, type a character in the text box at the top of the window and click Send. The program reacts to the characters '0' to '9' which are mapped to a PWM level between 0 and 255. All other characters are ignored.
  * Note that the speed is not necessarily linear to the PWM level. Depending on the fan a PWM level of 0 may mean a completely stopped fan or a low rotation speed.

![Serial Monitor window](pwm-serial-monitor.png)

## Other control mechanisms

In this example we used the serial monitor to control the PWM level because it requires no additional hardware.

You can add other mechanisms to control the fan. For example you can add a potentiometer that allows you to control the fan by turning a dial, or you could add a temperature sensor that allows you to increase the fan speed if the temperature gets too high.

## Monitoring fan speed

Note that we connected the tachometer pin to the Arduino even though we do not use it in ths program. It is possible to attach an interrupt to this pin in order to monitor the fan speed.

The following code increases the variable `tachCount` for every full rotation. In the main loop you can use this to calculate RPM values.

```c
#define TACH_PIN 2

volatile long tachCount = 0;

void tach() {
  tachCount++;
}

void setup(void) {
  // Add to setup method
  pinMode(TACH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TACH_PIN), tach, RISING);
}
```
