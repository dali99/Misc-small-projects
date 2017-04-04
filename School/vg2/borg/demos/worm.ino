// A single pxiel moves in a random direction over and over again
#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 54
#define DATA_PIN 7

#define WORM_COLOR (CRGB) 0x0000FF

int select;
LEDSelect head;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  initMap();
  randomSeed(analogRead(0));
  FastLED.clear();
  
  do {
      select = random(0, NUM_LEDS);
    }
  while (select == 5 || !(select % (9 + 5)));

  leds[select] = WORM_COLOR;
  FastLED.show();
  delay(500);
  
  encodeLED(select, &head);
  
}

void loop() {
  FastLED.clear();
  getNeighborLED(&head,random(0,4),&head);
  setColor(head, WORM_COLOR, leds);
  FastLED.show();
  delay(1000);
}
