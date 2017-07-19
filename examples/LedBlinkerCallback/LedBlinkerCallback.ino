/*
  LedBlinkerCallback

  Simple sketch to demostrate the use 
  of the MyBlinker Library to blink a LED
  and call a function when finished.

  The circuit:
  * A LED attached to pin 2.

  Created 13 July 2017
  By Evert Arias

  https://ariascode.github.io/MyBlinker

*/

#include "MyBlinker.h"

const int ledPin = 2; // Arduino pin where the LED is connected.

// PixelBlinker.
LedBlinker led(ledPin);

/* function to call when finished */
void finished(){
  // Blink
  led.blink(500  /* time on */, 
            100  /* time off */, 
            3    /* cycles */, 
            1000 /* pause between sequences */, 
            2    /* sequences */, 
            NULL /* function to call when finished */
            );
}

/* setup */
void setup(){
  // Blink
   led.blink(500      /* time on */, 
             100      /* time off */, 
             3        /* cycles */, 
             1000     /* pause between sequences */, 
             2        /* sequences */, 
             finished /* function to call when finished */
             );
}

/* loop */
void loop(){
  // Always call the "update" function in the loop.
  led.update();
}
