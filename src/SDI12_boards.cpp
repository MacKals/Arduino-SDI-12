/* ======================== Arduino SDI-12 =================================
   Arduino library for SDI-12 communications to a wide variety of environmental
   sensors. This library provides a general software solution, without requiring
   ======================== Arduino SDI-12 =================================*/

#include "SDI12_boards.h"

SDI12Timer::SDI12Timer(){
}

// Teensy 3.5 or Teensy 3.6
#if defined(__MK64FX512__) || defined(__MK66FX1M0__)

static uint8_t preSDI12_FTM0_SC;

void SDI12Timer::configSDI12TimerPrescale(void) {
        FTM0_MODE = FTM0_MODE | 0x00000004; // dissable write protect
        preSDI12_FTM0_SC = FTM0_SC;

        FTM0_SC = 0;

        FTM0_CNTIN = 0; //Set the Counter Initial Value to 0
        FTM0_CNT = 0x0; //FTM Counter Value - reset counter to zero
        FTM0_MOD = 960/2; // set mod to make count with period 15625us (like Mega)

        FTM0_SC = 0b01001011;
        // enable interrupt, use system clock and prescaler CK/8
        // Serial.println(FTM0_SC);
        // Serial.println(FTM0_MOD);
        FTM0_MODE = FTM0_MODE & 0xFFFFFFFb; // dissable write protect

        NVIC_ENABLE_IRQ(IRQ_FTM0);
}

void SDI12Timer::resetSDI12TimerPrescale(void) {
        FTM0_MODE = FTM0_MODE | 0x00000004; // dissable write protect
        FTM0_SC = preSDI12_FTM0_SC;
        FTM0_MODE = FTM0_MODE & 0xFFFFFFFb; // dissable write protect
}


// Unknown board
#else
#error "Please define your board timer and pins"
#endif
