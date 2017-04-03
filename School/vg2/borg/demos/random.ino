#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 45
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  
  randomSeed(analogRead(0));
}

void loop() {
  FastLED.clear();
  FastLED.show();
  
  for (int i = 0; i < NUM_LEDS; i++) {
    int select;
    do {
      select = random(0, NUM_LEDS);
    }
    while (leds[select] != (CRGB) 0x0);
    leds[select] = (CRGB) random(1, 0x1000000);
    FastLED.show();
    delay(250);
  }
  delay(1000);
}
