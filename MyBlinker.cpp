/*
 MyBlinker.cpp - A LED blinker library for Arduino platform.
 Created by Evert Arias. July 13, 2017.
 MyBlinker is provided Copyright © 2017 under MIT License.
*/

#include "Arduino.h"
#include "MyBlinker.h"

/* LedBlinker */

LedBlinker::LedBlinker(byte const pin): mPin(pin), mStartTime(0){
  mPolarity = COMMON_NEGATIVE;
  pinMode(pin, OUTPUT);
  if(mPolarity == COMMON_NEGATIVE){
    digitalWrite(pin, LOW);
  } else if(mPolarity == COMMON_POSITIVE){
    digitalWrite(pin, HIGH);
  }
}

LedBlinker::LedBlinker(byte const pin, uint8_t polarity): mPin(pin), mPolarity(polarity), mStartTime(0){
  pinMode(pin, OUTPUT);
  if(mPolarity == COMMON_NEGATIVE){
    digitalWrite(pin, LOW);
  } else if(mPolarity == COMMON_POSITIVE){
    digitalWrite(pin, HIGH);
  }
}

void LedBlinker::setPin(byte const pin){
   mPin = pin;
   pinMode(pin, OUTPUT);
   if(mPolarity == COMMON_NEGATIVE){
     digitalWrite(pin, LOW);
   } else if(mPolarity == COMMON_POSITIVE){
     digitalWrite(pin, HIGH);
   }
   mStartTime = 0;
}

void LedBlinker::setPolarity(uint8_t polarity){
  mPolarity = polarity;
  if(mPolarity == COMMON_NEGATIVE){
    digitalWrite(mPin, LOW);
  } else if(mPolarity == COMMON_POSITIVE){
    digitalWrite(mPin, HIGH);
  }
}

void LedBlinker::blink(unsigned int const onDuration,
  unsigned int const offDuration,
  byte const blinks,
  unsigned int const pauseDuration,
  unsigned int const sequences,
  void (*finishedCallbackFunction)()){
    mOnDuration = onDuration ? max(MINIMUM_INTERVAL, onDuration) : 0;
    mOffDuration = offDuration ? max(MINIMUM_INTERVAL, offDuration) : 0;
    mBlinks = blinks;
    mPauseDuration = pauseDuration ? max(MINIMUM_INTERVAL, pauseDuration) : 0;;
    mSequences = sequences;
    mFinishedCallbackFunction = finishedCallbackFunction;
    mStartTime = max(millis(), 1);
    mLastRunTime = 0;
    update();
}

void LedBlinker::on(){
  blink(1, 0, 1, 0, 0, NULL);
}

void LedBlinker::off(){
  blink(0, 0, 0, 1, 0, NULL);
}

void LedBlinker::onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)()){
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void LedBlinker::offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)()){
  blink(0, 0, 0, offDuration, 1, finishedCallbackFunction);
}

void LedBlinker::update(){
  unsigned long currentTime = millis();

  if (currentTime - mLastRunTime < MINIMUM_INTERVAL) {
    return;
  }
  mLastRunTime = currentTime;
  if (!mStartTime || !mPin) {
    return;
  }

  unsigned long elapsedTime = currentTime - mStartTime;
  unsigned int blinkDuration = mOnDuration + mOffDuration;
  unsigned int sequenceDuration = blinkDuration * mBlinks + mPauseDuration - mOffDuration;

  if (!sequenceDuration ||
    (mSequences != 0 && elapsedTime / sequenceDuration >= mSequences)) {
      mStartTime = 0;
      if (mFinishedCallbackFunction) {
        mFinishedCallbackFunction();
      }
      return;
    }

    // Figure out where we are within a sequence
    unsigned int blinkingDuration = blinkDuration * mBlinks;
    unsigned int timeInSequence = elapsedTime % sequenceDuration;
    if (timeInSequence < blinkingDuration && timeInSequence % blinkDuration < mOnDuration) {
      if(mPolarity == COMMON_NEGATIVE){
        digitalWrite(mPin, HIGH);
      } else if (mPolarity == COMMON_POSITIVE){
        digitalWrite(mPin, LOW);
      }
    } else {
      if(mPolarity == COMMON_NEGATIVE){
        digitalWrite(mPin, LOW);
      } else if(mPolarity == COMMON_POSITIVE){
        digitalWrite(mPin, HIGH);
      }
    }
}



/* PixelLedBlinker */

PixelBlinker::PixelBlinker(byte const pin, unsigned int const numPixels): mPin(pin), mNumPixels(numPixels), mStartTime(0){
  pinMode(pin, OUTPUT);
  neoPixel.begin();
}

PixelBlinker::PixelBlinker(byte const pin, unsigned int const numPixels, neoPixelType neoPixelType): mPin(pin), mNumPixels(numPixels), mNeoPixelType(neoPixelType), mStartTime(0){
  pinMode(pin, OUTPUT);
  neoPixel.begin();
}

void PixelBlinker::setPin(byte const pin){
  mPin = pin;
  pinMode(pin, OUTPUT);
  mStartTime = 0;
}

void PixelBlinker::setNumPixels(unsigned int const numPixels){
  mNumPixels = numPixels;
}

void PixelBlinker::setPixel(const int pixelId){
  mPixelId = pixelId;
}

void PixelBlinker::setPixelColor(const PixelColor& pixelColor){
  mPixelColor = pixelColor;
}

void PixelBlinker::setPixelBrightness(const byte pixelBrightness){
  mPixelBrightness = pixelBrightness;
}

void PixelBlinker::setPixelBrightnessPercent(const byte pixelBrightnessPercent){
  mPixelBrightness = ((pixelBrightnessPercent * 255) / 100);
}

void PixelBlinker::blink(unsigned int const onDuration,
  unsigned int const offDuration,
  byte const blinks,
  unsigned int const pauseDuration,
  unsigned int const sequences,
  void (*finishedCallbackFunction)()){
    mOnDuration = onDuration ? max(MINIMUM_INTERVAL, onDuration) : 0;
    mOffDuration = offDuration ? max(MINIMUM_INTERVAL, offDuration) : 0;
    mBlinks = blinks;
    mPauseDuration = pauseDuration ? max(MINIMUM_INTERVAL, pauseDuration) : 0;;
    mSequences = sequences;
    mFinishedCallbackFunction = finishedCallbackFunction;
    mStartTime = max(millis(), 1);
    mLastRunTime = 0;
    update();
}

// No argument provided
void PixelBlinker::on(){
    blink(1, 0, 1, 0, 0, NULL);
}

// Pixel id provided
void PixelBlinker::on(const int pixelId){
  mPixelId = pixelId;
  blink(1, 0, 1, 0, 0, NULL);
}

// Pixel id and color provided
void PixelBlinker::on(const int pixelId, const PixelColor& pixelColor){
  mPixelId = pixelId;
  mPixelColor = pixelColor;
  blink(1, 0, 1, 0, 0, NULL);
}

// All arguments provided
void PixelBlinker::on(const int pixelId, const PixelColor& pixelColor, const byte pixelBrightness){
  mPixelId = pixelId;
  mPixelColor = pixelColor;
  mPixelBrightness = pixelBrightness;
  blink(1, 0, 1, 0, 0, NULL);
}

void PixelBlinker::off(){
  blink(0, 0, 0, 1, 0, NULL);
}

void PixelBlinker::off(const int pixelId){
  mPixelId = pixelId;
  blink(0, 0, 0, 1, 0, NULL);
}

void PixelBlinker::onUntil(unsigned int const onDuration, void (*finishedCallbackFunction)()){
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void PixelBlinker::onUntil(const int pixelId, unsigned int const onDuration, void (*finishedCallbackFunction)()){
  mPixelId = pixelId;
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void PixelBlinker::onUntil(const int pixelId, const PixelColor& pixelColor, unsigned int const onDuration, void (*finishedCallbackFunction)()){
  mPixelId = pixelId;
  mPixelColor = pixelColor;
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void PixelBlinker::onUntil(const int pixelId, const PixelColor& pixelColor, const byte pixelBrightness, unsigned int const onDuration, void (*finishedCallbackFunction)()){
  mPixelId = pixelId;
  mPixelColor = pixelColor;
  mPixelBrightness = pixelBrightness;
  blink(onDuration, 0, 1, 0, 1, finishedCallbackFunction);
}

void PixelBlinker::offUntil(unsigned int const offDuration, void (*finishedCallbackFunction)()){
  blink(0, 0, 0, offDuration, 1, finishedCallbackFunction);
}

void PixelBlinker::offUntil(const int pixelId, unsigned int const offDuration, void (*finishedCallbackFunction)()){
  mPixelId = pixelId;
  blink(0, 0, 0, offDuration, 1, finishedCallbackFunction);
}

void PixelBlinker::update(){
  unsigned long currentTime = millis();

  if (currentTime - mLastRunTime < MINIMUM_INTERVAL) {
    return;
  }
  mLastRunTime = currentTime;
  if (!mStartTime || !mPin) {
    return;
  }

  unsigned long elapsedTime = currentTime - mStartTime;
  unsigned int blinkDuration = mOnDuration + mOffDuration;
  unsigned int sequenceDuration = blinkDuration * mBlinks + mPauseDuration - mOffDuration;

  if (!sequenceDuration ||
    (mSequences != 0 && elapsedTime / sequenceDuration >= mSequences)) {
      mStartTime = 0;
      if (mFinishedCallbackFunction) {
        mFinishedCallbackFunction();
      }
      return;
    }

    // Figure out where we are within a sequence
    unsigned int blinkingDuration = blinkDuration * mBlinks;
    unsigned int timeInSequence = elapsedTime % sequenceDuration;
    if (timeInSequence < blinkingDuration && timeInSequence % blinkDuration < mOnDuration) {
      neoPixel.setPixelColor(mPixelId, mPixelColor.getPackedRGB());
      neoPixel.setBrightness(mPixelBrightness);
      neoPixel.show();
    } else {
      neoPixel.setPixelColor(mPixelId, neoPixel.Color(0, 0, 0));
      neoPixel.show();
    }
}
