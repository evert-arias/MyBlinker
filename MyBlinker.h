/*
 MyBlinker.h - A LED blinker library for Arduino platform.
 Created by Evert Arias. July 13, 2017.
 MyBlinker is provided Copyright © 2017 under MIT License.
*/

#ifndef MyBlinker_h
#define MyBlinker_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

#define MINIMUM_INTERVAL 20
#define COMMON_NEGATIVE 0
#define COMMON_POSITIVE 1

class PixelColor {
  private:
    int my_r;
    int my_g;
    int my_b;
  public:
    PixelColor (int red, int green, int blue): my_r(red),my_g(green),my_b(blue){}
    int r() const {return my_r;}
    int b() const {return my_b;}
    int g() const {return my_g;}
    uint32_t getPackedGRB(){
      return ((uint32_t)my_r << 16) | ((uint32_t)my_g <<  8) | my_b;
    }
    uint32_t getPackedRGB(){
      return ((uint32_t)my_g << 16) | ((uint32_t)my_r <<  8) | my_b;
    }
};

class LedBlinker {
private:
	byte mPin;
  uint8_t mPolarity = COMMON_NEGATIVE;
	byte mBlinks;
	unsigned int mOnDuration;
	unsigned int mOffDuration;
	unsigned int mPauseDuration;
	unsigned int mSequences;
	unsigned long mStartTime;
	unsigned long mLastRunTime;
	void (*mFinishedCallbackFunction)();
public:
  LedBlinker(byte const pin);
	LedBlinker(byte const pin, uint8_t ledPolarity);
	void setPin(byte const pin);
  void setPolarity(uint8_t polarity);
	void blink(unsigned int const onDuration,
		unsigned int const offDuration,
		byte const blinks,
		unsigned int const pauseDuration,
		unsigned int const sequences,
	  void (*finishedCallbackFunction)());
	void on();
	void off();
	void onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)());
	void offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)());
	void update();
};

class PixelBlinker {
private:
	byte mPin;
	unsigned int mNumPixels;
  int mPixelId = 0;
  PixelColor mPixelColor = PixelColor(0, 0, 255);
  byte mPixelBrightness = 127;
	byte mBlinks;
  neoPixelType mNeoPixelType = NEO_GRB + NEO_KHZ800;
	unsigned int mOnDuration;
	unsigned int mOffDuration;
	unsigned int mPauseDuration;
	unsigned int mSequences;
	unsigned long mStartTime;
	unsigned long mLastRunTime;
	void (*mFinishedCallbackFunction)();
  Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(mNumPixels, mPin, mNeoPixelType);
public:
  PixelBlinker(byte const pin, unsigned int const numLeds);
	PixelBlinker(byte const pin, unsigned int const numLeds, neoPixelType neoPixelType);
	void setPin(byte const pin);
	void setNumPixels(unsigned int const numPixels);
  void setPixel(const int pixelId);
  void setPixelColor(const PixelColor& pixelColor);
  void setPixelBrightness(const byte pixelBrightness);
  void setPixelBrightnessPercent(const byte pixelBrightnessPercent);
	void blink(unsigned int const onDuration,
		unsigned int const offDuration,
		byte const blinks,
		unsigned int const pauseDuration,
		unsigned int const sequences,
		void (*finishedCallbackFunction)());
  void on();
  void on(const int pixelId);
  void on(const int pixelId, const PixelColor& pixelColor);
	void on(const int pixelId, const PixelColor& pixelColor, const byte pixelBrightness);
	void off();
  void off(const int pixelId);
	void onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)());
  void onUntil(const int pixelId, unsigned int const onDuration, void (*finishedCallbackFunction)());
  void onUntil(const int pixelId, const PixelColor& pixelColor, unsigned int const onDuration, void (*finishedCallbackFunction)());
  void onUntil(const int pixelId, const PixelColor& pixelColor, const byte pixelBrightness, unsigned int const onDuration, void (*finishedCallbackFunction)());
  void offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)());
  void offUntil(const int pixelId, unsigned int const offDuration, void (*finishedCallbackFunction)());
  void update();
};

#endif
