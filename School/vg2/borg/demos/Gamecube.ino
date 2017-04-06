#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 54
#define DATA_PIN 7

#define COLOR (CRGB) 0x0000FF

CRGB leds[NUM_LEDS];

LEDSelect head;

void setup() {
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  initMap();
  FastLED.clear();
}

void loop() {
  setColor({4, 1, 0}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({4, 0, 0}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({4, 0, 1}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({4, 0, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  
  setColor({0, 0, 0}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({0, 0, 1}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({0, 0, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({0, 0, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({0, 1, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({0, 2, 2}, COLOR, leds);
  FastLED.show();
  delay(280);

  setColor({1, 0, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({1, 1, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({1, 2, 2}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({1, 2, 1}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({1, 2, 0}, COLOR, leds);
  FastLED.show();
  delay(280);
  setColor({1, 1, 0}, COLOR, leds);
  FastLED.show();
  
  delay(320);

  setColor({1, 0, 0}, COLOR, leds);
  setColor({4, 2, 2}, COLOR, leds);
  setColor({0, 2, 0}, COLOR, leds);
  FastLED.show();
  
  delay(2000);
  FastLED.clear();
}
