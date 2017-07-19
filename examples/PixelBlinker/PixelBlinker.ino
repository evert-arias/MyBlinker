/*
  PixelBlinker

  Simple sketch to demostrate the use 
  of the MyBlinker Library to blink a NeoPixel LED.

  The circuit:
  * A NeoPixel LED attached to pin 2.

  Created 13 July 2017
  By Evert Arias

  https://ariascode.github.io/MyBlinker

*/

#include "MyBlinker.h"

const int pixelPin = 2; // Arduino pin where the NeoPixel LED is connected.
const int pixels = 1;   // Amount of NeoPixel LEDs connected.

// PixelBlinker.
PixelBlinker pixel(pixelPin, pixels);

PixelColor red(255, 0, 0);    // Red color
PixelColor blue(0, 0, 255);   // Blue color
PixelColor green(0, 255, 0);  // Green color

/* setup */
void setup(){
  // Set the pixel color
  pixel.setPixelColor(red);
  // Blink
  pixel.blink(500  /* time on */, 
              100  /* time off */, 
              3    /* cycles */, 
              1000 /* pause between sequences */, 
              2    /* sequences */, 
              NULL /* function to call when finished */
              );
}

/* loop */
void loop(){
  // Always call the "update" function in the loop.
  pixel.update();
}
