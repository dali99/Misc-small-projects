#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 54
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  
  randomSeed(analogRead(0));
}

void loop()
{
  int select = random(0, NUM_LEDS);
  leds[select] = (CRGB) random(1, 0x1000000);
  FastLED.show();
}
