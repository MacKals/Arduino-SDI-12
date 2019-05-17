/* ======================== Arduino SDI-12 =================================
Arduino library for SDI-12 communications to a wide variety of environmental
sensors. This library provides a general software solution, without requiring
   ======================== Arduino SDI-12 =================================*/

#ifndef SDI12_boards_h
#define SDI12_boards_h

#include <Arduino.h>

class SDI12Timer
{
public:
    SDI12Timer();
    void configSDI12TimerPrescale(void);
    void resetSDI12TimerPrescale(void);

// Teensy 3.5 or Teensy 3.6
#if defined(__MK64FX512__) || defined(__MK66FX1M0__)

    // Library is implemented to generate a 16MHz counter so that the timing
    // commands from the Arduino implementation of this library can be used.


    // For Teensy 3.5
    #define PRESCALE_IN_USE_STR "13"
    #define TICKS_PER_BIT 13
    // 16MHz / 1024 prescaler = 15624 'ticks'/sec = 64 µs / 'tick'
    // (1 sec/1200 bits) * (1 tick/64 µs) = 13.0208 ticks/bit

    #define BITS_PER_TICK_Q10 79
    // 1/(13.0208 ticks/bit) * 2^10 = 78.6432
    #define RX_WINDOW_FUDGE 2

// Unknown board
#else
#error "Please define your board timer and pins"
#endif

};

#endif
