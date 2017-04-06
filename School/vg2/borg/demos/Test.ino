#include <FastLED.h>
#include <borg.h>

#define NUM_SIDES 6
#define NUM_LEDS 9 * NUM_SIDES
#define DATA_PIN 7

#define COLOR (CRGB) 0x0000FF

CRGB leds[NUM_LEDS];

LEDSelect head;

void setup() {
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  initMap();
  FastLED.clear();
  encodeLED(1, &head);
}
void loop() {
  // Test induidual leds
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    leds[i] = COLOR;
    FastLED.show();
    delay(300);
  }

  FastLED.clear();

  // Test setColor functions
  // Whole sides
  for (int i = 0; i < NUM_SIDES; i++) {
    FastLED.clear();
    setColor({i, 255, 255}, COLOR, leds);
    FastLED.show();
    delay(500);
  }

  FastLED.clear();

  // whole columns
  for (int i = 0; i < NUM_SIDES; i++) {
    for (int j = 0; j < 3; j++) {
      FastLED.clear();
      setColor({i, j, 255}, COLOR, leds);
      FastLED.show();
      delay(250);
    }
  }

  FastLED.clear();

  // Whole rows
  for (int i = 0; i < NUM_SIDES; i++) {
    for (int j = 0; j < 3; j++) {
      FastLED.clear();
      setColor({i, 255, j}, COLOR, leds);
      FastLED.show();
      delay(250);
    }
  }

  // single pixels
  for (int i = 0; i < NUM_SIDES; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        FastLED.clear();
        setColor({i, j, k}, COLOR, leds);
        FastLED.show();
        delay(250);
      }
    }
  }

  FastLED.clear();

  // Test Neighbor Rotation horizontal
  LEDSelect head = {2, 1, 1};
  for (int i = 0; i < 12; i++) {
    setColor(head, COLOR, leds);
    FastLED.show();
    getRotNeighborLED(&head, RIGHT, &head);
    delay(250);
  }

  FastLED.clear();

  // Test neighbot Rotation Vertical
  head = {2, 1, 1};
  for (int i = 0; i < 12; i++) {
    setColor(head, COLOR, leds);
    FastLED.show();
    getRotNeighborLED(&head, UP, &head);
    delay(250);
  }

  delay(1000);
  FastLED.clear();

  // Test Neighbor Rotation horizontal
  head = {2, 1, 0};
  for (int i = 0; i < 12; i++) {
    setColor(head, COLOR, leds);
    FastLED.show();
    getRotNeighborLED(&head, RIGHT, &head);
    delay(250);
  }

  // Test Neighbor Rotation horizontal
  head = {2, 1, 2};
  for (int i = 0; i < 12; i++) {
    setColor(head, COLOR, leds);
    FastLED.show();
    getRotNeighborLED(&head, RIGHT, &head);
    delay(250);
  }

  FastLED.clear();

  // Test neighbot Rotation Vertical
  head = {2, 1, 1};
  for (int i = 0; i < 12; i++) {
    setColor(head, COLOR, leds);
    FastLED.show();
    getRotNeighborLED(&head, UP, &head);
    delay(250);
  }

}
