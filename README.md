# MyBlinker Arduino Library

[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

A LED blinker library for the Arduino platform.

> **New:** This library now supports **NeoPixel** LEDs.

## Introduction

This library allows you to perform blinking operations with LEDs. Since it also operates with NeoPixels, it depends on [Adafruit_NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel), so you must have it installed in your environment in order for it to compile.

The library provides three classes:

#### LedBlinker

This class allows you to blink a LED.

#### PixelBlinker

This class allows you to blink a **NeoPixel**.

#### PixelColor

This class allows you to create a color object for the **PixelBlinker** class.

## LedBlinker

### The Class

The **LedBlinker** class allows you to create an instance of the LED you want to operate. The class constructor takes two values as arguments. The **first argument** is the pin where the LED is connected. The **second argument** is **optional** to define the polarity of the LED. If this argument is not provided, the LED polarity will be set to common negative by default.

```cpp
/* LedBlinker Instance.
 * First argument: The pin where the LED is connected.
 * Second argument: Optional argument to define the LED polarity.
   Allowed values:
                  COMMON_NEGATIVE
                  COMMON_POSITIVE
 */
LedBlinker myBlueLed(13, COMMON_POSITIVE);
```

### Methods

```cpp
/* Set the pin where the LED is connected. */
myBlueLed.setPin(pin);
```

```cpp
/* Set the LED polarity.
 * Allowed values: COMMON_NEGATIVE, COMMON_POSITIVE.
 */
myBlueLed.setPolarity(COMMON_NEGATIVE);
```

```cpp
/* Turn On the LED. */
myBlueLed.on();
```

```cpp
/* Turn Off the LED. */
myBlueLed.off();
```

```cpp
/* Turn On the LED for the time of "onDuration" then call the "onFinished" method. */
myBlueLed.onUntil(onDuration, onFinished);
```

```cpp
/* Turn Off the LED for the time of "offDuration" then call the "onFinished" method. */
myBlueLed.offUntil(offDuration, onFinished);
```

```cpp
/* Blink the LED.
 * The LED will be On for the time of "onDuration".
 * The LED will be Off for the time of "offDuration".
 * That blink will be repeated the number of times defined by "blinks".
 * Then a pause define by "pauseDuration".
 * That sequency will repeat as many time as defined by "sequences".
 * At the end of all sequences the "onFinished" method will be called.
 */
 myBlueLed.blink(onDuration, offDuration, blinks, pauseDuration, sequences, onFinished);
```

```cpp
 /* Allways call this method in the loop. */
 myBlueLed.update();
```

## PixelBlinker

### The Class

The **PixelBlinker** class allows you to create an instance of the **NeoPixel** you want to operate. The class constructor takes three values as arguments. The **first argument** is the pin where the **NeoPixel** is connected. The **second argument** is the amount of NeoPixel connected together. The **third argument** is **optional** to define the type of **NeoPixel**.

```cpp
/* PixelBlinker Instance.
 * First argument: The number of the pin where the NeoPixel is connected.
 * Second argument: The amount of NeoPixel connected together.
 * Third argument: Optional argument to define the NeoPixel type.
   Pixel types:
                NEO_GRB + NEO_KHZ800
                NEO_GRB + NEO_KHZ400
                NEO_RGB + NEO_KHZ800
                NEO_RGB + NEO_KHZ400
   If this argument is not provided the NeoPixel type will be set to NEO_GRB + NEO_KHZ800 by default.         
 */
PixelBlinker myNeoPixel(pixelPin, pixels, NEO_GRB + NEO_KHZ800);
```

### Methods

```cpp
/* Set the pin where the NeoPixel is connected. */
myNeoPixel.setPin(pin);
```

```cpp
/* Set the amount of Pixel connected. */
myNeoPixel.setNumPixels(numPixels);
```

```cpp
/* Set the Pixel that you want to operate. */
myNeoPixel.setPixel(pixelId);
```

```cpp
/* Set the color of the Pixel. The argument must be a PixelColor object. */
myNeoPixel.setPixelColor(pixelColor);
```

```cpp
/* Set the Pixel brightness, 0 - 255 value. */
myNeoPixel.setPixelBrightness(pixelBrightness);
```

```cpp
/* Set the Pixel brightness using percentage. */
myNeoPixel.setPixelBrightnessPercent(pixelBrightnessPercent);
```

```cpp
/* Turn On the Pixel. */
myNeoPixel.on();
```

```cpp
/* Turn On the Pixel by it's Id. */
myNeoPixel.on(pixelId);
```

```cpp
/* Turn Off the Pixel. */
myNeoPixel.off();
```

```cpp
/* Turn Off the Pixel by it's Id. */
myNeoPixel.off(pixelId);
```

```cpp
/* Turn On the Pixel for the time of "onDuration" then call the "onFinished" method. */
myNeoPixel.onUntil(onDuration, onFinished);
```

```cpp
/* Turn On the Pixel by it's Id, for the time of "onDuration" then call the "onFinished" method. */
myNeoPixel.onUntil(pixelId, onDuration, onFinished);
```

```cpp
/* Turn Off the Pixel for the time of "offDuration" then call the "onFinished" method. */
myNeoPixel.offUntil(offDuration, onFinished);
```

```cpp
/* Turn Off the Pixel by it's Id, for the time of "onDuration" then call the "onFinished" method. */
myNeoPixel.offUntil(pixelId, offDuration, onFinished);
```

```cpp
/* Blink the Pixel.
 * Argument "onDuration": The time that the pixel will be On in the cycle.
 * Argument "offDuration": The time that the pixel will be Off in the cycle.
 * Argument "blinks": The number of times to blink the Pixel.
 * Argument "pauseDuration": The time to wait between sequences.
 * Argument "sequences": The number of times to repeat the sequence.
 * Argument "onFinished": The function to call when finished.
 */
 myNeoPixel.blink(onDuration, offDuration, blinks, pauseDuration, sequences, onFinished);
```

```cpp
 /* It is always necessary to call this method in the loop. */
 myNeoPixel.update();
```

## PixelColor

### The Class

The **PixelColor** class allows you to create a color object to be use with the PixelBlinker class. You may create as many color objects as you need with your custom color values.

```cpp
/* Red color object to be used by PixelBlinker */
PixelColor red(255, 0, 0);
```

```cpp
/* Green color object to be used by PixelBlinker */
PixelColor green(0, 255, 0);
```

```cpp
/* Blue color object to be used by PixelBlinker */
PixelColor blue(0, 0, 255);
```

```cpp
/* Custom color object to be used by PixelBlinker */
PixelColor myCustomColor(100, 100, 255);
```

### Methods

> Normal use of this class does not require using any of these methods.

```cpp
/* Returns the red value of the color. */
myCustomColor.r();
```

```cpp
/* Returns the green value of the color. */
myCustomColor.g();
```

```cpp
/* Returns the blue value of the color. */
myCustomColor.b();
```

```cpp
/* Returns the packed value of the color in RGB format. */
myCustomColor.getPackedRGB();
```

```cpp
/* Returns the packed value of the color in GRB format. */
myCustomColor.getPackedGRB();
```

## Copyright

MyBlinker is provided Copyright © 2017 under [MIT](https://github.com/ariascode/MyBlinker/blob/master/LICENSE.md) License.
