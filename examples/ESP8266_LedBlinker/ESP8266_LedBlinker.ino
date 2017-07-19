/*
  ESP8266_LedBlinker

  Simple sketch to demostrate the use 
  of the MyBlinker Library to blink a LED.

  The circuit:
  * A LED attached to pin 2.

  Created 13 July 2017
  By Evert Arias

  https://ariascode.github.io/MyBlinker

*/

#include "MyBlinker.h"

/* PixelBlinker instance */
LedBlinker led(LED_BUILTIN, COMMON_POSITIVE);

/* setup */
void setup(){
  // Blink
   led.blink(500  /* time on */, 
             100  /* time off */, 
             3    /* cycles */, 
             1000 /* pause between secuences */, 
             2    /* secuences */, 
             NULL /* function to call when finished */
             );
}

/* loop */
void loop(){
  // Always call the "update" function in the loop
  led.update();
}
