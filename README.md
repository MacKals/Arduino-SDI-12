Arduino-SDI-12-Teensy35
==============

A modified version of [Arduino-SDI-12](https://github.com/EnviroDIY/Arduino-SDI-12) for the Teensy 3.5. 

Arduino library for SDI-12 communications to a wide variety of environmental sensors. This library provides a general software solution, without requiring any additional hardware, to implement the SDI-12 communication protocol between an Arduino-based data logger and SDI-12-enabled sensors.

[SDI-12](http://www.sdi-12.org/) is an asynchronous, ASCII, serial communications protocol that was developed for intelligent sensory instruments that typically monitor environmental data. [Advantages of SDI-12](http://en.wikipedia.org/wiki/SDI-12) include the ability to use a single available data channel for many sensors.

## Getting Started

Learn more, below, about this library's:
* [Origins and Inherited Limitations](https://github.com/EnviroDIY/Arduino-SDI-12#origins-and-inherited-limitations);
* [Compatibility Considerations](https://github.com/EnviroDIY/Arduino-SDI-12#compatibility-considerations);
* [Variants and Branches](https://github.com/EnviroDIY/Arduino-SDI-12#variants-and-branches) we created to overcome some limitations.

Try running our [Example sketches](https://github.com/EnviroDIY/Arduino-SDI-12/tree/master/examples) with your Arduino board and SDI-12 sensor.

Dive into the details of how this library works by reading the documentation in our [Arduino-SDI-12 wiki](https://github.com/StroudCenter/Arduino-SDI-12/wiki).  [Note:  this is currently somewhat out of date.  Sorry!]


## Origins and Inherited Limitations

This library was developed from the [SoftwareSerial](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/SoftwareSerial) library that is a built-in [standard Arduino library](https://www.arduino.cc/en/Reference/Libraries). It was further modified to use a timer to improve read stability and decrease the amount of time universal interrupts are disabled using logic from [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial).

The most obvious "limitation" is that this library will conflict with all other libraries that make use of pin change interrupts.  You will be unable to compile them together.  Some other libraries using pin change interrupts include [SoftwareSerial](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/SoftwareSerial), [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial), [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt/), [PinChangeInt](https://playground.arduino.cc/Main/PinChangeInt), [Servo](https://www.arduino.cc/en/Reference/Servo), and quite a number of other libraries.  See the notes under [Variants and Branches](https://github.com/EnviroDIY/Arduino-SDI-12#variants-and-branches) below for advice in using this library in combination with such libraries.

Another non-trivial, but hidden limitation is that _all_ interrupts are disabled during most of the transmission of each character, which can interfere with other processes. That includes other pin-change interrupts, clock/timer interrupts, external interrupts, and every other type of processor interrupt.  This is particularly problematic for Arduino-SDI-12, because SDI-12 operates at a very slow baud rate (only 1200 baud). This translates to ~8.3 mS of "radio silence" from the processor for each character that goes out via SDI-12, which adds up to ~380-810ms per command!  Interrupts are enabled for the majority of the time while the processor is listening for responses.

For most AVR boards, this library will also conflict with the [tone](https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/) function because of its utilization of timer 2.  There will be no obvious compile error, but because SDI-12 and the tone library may use different clock-prescaler functions, the results for both might be rather unexpected.  All 8MHz AVR boards will also have unresolvable prescaler conflicts with [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial).  The pre-scaler values needed for the SDI-12 functionality are set in the begin() function and reset to their original values in the end() function.

## Compatibility Considerations

This library is made for Teensy 3.5.

Not all data pins are available for use with this Arduino-SDI-12 library. Pin availability depends on the micro-controller. All _RX_ pins should work to drive the data-line, including D1, D9, D31, D34 etc.


## License
The SDI12 library code is released under the GNU Lesser Public License (LGPL 2.1) -- See [LICENSE-examples.md](https://github.com/EnviroDIY/Arduino-SDI-12/blob/master/LICENSE) file for details.

Example Arduino sketches are released under the BSD 3-Clause License -- See [LICENSE-examples.md](https://github.com/EnviroDIY/Arduino-SDI-12/blob/master/LICENSE.md) file for details.

Documentation is licensed as [Creative Commons Attribution-ShareAlike 4.0](https://creativecommons.org/licenses/by-sa/4.0/) (CC-BY-SA) copyright.

## Credits
[EnviroDIY](http://envirodiy.org/)™ is presented by the Stroud Water Research Center, with contributions from a community of enthusiasts sharing do-it-yourself ideas for environmental science and monitoring.

[Kevin M. Smith](https://github.com/Kevin-M-Smith) was the primary developer of the Arduino-SDI-12 library, with input from [S. Hicks](https://github.com/s-hicks2) and [Anthony Aufdenkampe](https://github.com/aufdenkampe).

[Sara Damiano](https://github.com/SRGDamia1) is now the primary maintainer, with input from many [other contributors](https://github.com/EnviroDIY/Arduino-SDI-12/graphs/contributors).

This project has benefited from the support from the following funders:

* National Science Foundation, awards [EAR-0724971](http://www.nsf.gov/awardsearch/showAward?AWD_ID=0724971), [EAR-1331856](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1331856), [ACI-1339834](http://www.nsf.gov/awardsearch/showAward?AWD_ID=1339834)
* William Penn Foundation, grant 158-15
* Stroud Water Research Center endowment
