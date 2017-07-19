/*
  TwoPixelsBlinker

  Simple sketch to demostrate the use 
  of the MyBlinker Library to blink two NeoPixel LED.

  The circuit:
  * A NeoPixel LED attached to pin 2.
  * A NeoPixel LED attached to the output Pin of the former.

  Created 13 July 2017
  By Evert Arias

  https://ariascode.github.io/MyBlinker

*/

#include "MyBlinker.h"

const int pixelPin = 2; // Arduino pin where the NeoPixel LED it's connected.
const int pixels = 2;   // Amount of NeoPixel LEDs connected.

// PixelBlinker.
PixelBlinker pixel(pixelPin, pixels);

PixelColor red(255, 0, 0);    // Red color
PixelColor blue(0, 0, 255);   // Blue color
PixelColor green(0, 255, 0);  // Green color

/* function to call when finished */
void finished(){
  // Set the pixel to operate
  pixel.setPixel(1);
  // Set the pixel color
  pixel.setPixelColor(blue);
  // Blink
  pixel.blink(500  /* time on */, 
              100  /* time off */, 
              3    /* cycles */, 
              1000 /* pause between sequences */, 
              2    /* sequences */, 
              NULL /* function to call when finished */
              );
}

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
              finished /* function to call when finished */
              );
}

/* loop */
void loop(){
  // Always call the "update" function in the loop.
  pixel.update();
}
