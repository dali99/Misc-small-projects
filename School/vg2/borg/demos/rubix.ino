// A single pxiel moves in a random direction over and over again
#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 54
#define DATA_PIN 7

#define BLUE (CRGB) 0x0000FF
#define RED (CRGB) 0xFF0000
#define GREEN (CRGB) 0x00FF00
#define ORANGE (CRGB) 0xFF7000
#define WHITE (CRGB) 0xFFFFFF
#define YELLOW (CRGB) 0xFFFF00

CRGB leds[NUM_LEDS];
CRGB solution[NUM_LEDS];
byte METAROTTODIR[6];

void rubixRot(byte side, bool dir);

void setup() {
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
  initMap();
  
  METAROTTODIR[0]=CLOCKW;
  METAROTTODIR[1]=UP;
  METAROTTODIR[2]=ACLOCKW;
  METAROTTODIR[3]=DOWN;
  METAROTTODIR[4]=LEFT;
  METAROTTODIR[5]=RIGHT;
  
  randomSeed(analogRead(0));
  FastLED.clear();
  FastLED.show();

  // Make the solution memory structure
  setColor({0, 255, 255}, BLUE, solution);
  setColor({1, 255, 255}, RED, solution);
  setColor({2, 255, 255}, GREEN, solution);
  setColor({3, 255, 255}, ORANGE, solution);
  setColor({4, 255, 255}, WHITE, solution);
  setColor({5, 255, 255}, YELLOW, solution);

  setColor({0, 1, 1}, BLUE, leds);
  setColor({1, 1, 1}, RED, leds);
  setColor({2, 1, 1}, GREEN, leds);
  setColor({3, 1, 1}, ORANGE, leds);
  setColor({4, 1, 1}, WHITE, leds);
  setColor({5, 1, 1}, YELLOW, leds);

  for (byte i = 0; i < 6; i++) {
    FastLED.show();
    delay(500);
    for (byte j = 0; j < 8; j++) {
      byte selection;
      do {
        selection = random(0, NUM_LEDS);
      }
      while (leds[selection] != (CRGB) 0x000000);
      
      switch (i) {
      case 0:
         leds[selection] = BLUE;
         break;
      case 1:
        leds[selection] = RED;
        break;
      case 2:
        leds[selection] = GREEN;
        break;
      case 3:
        leds[selection] = ORANGE;
        break;
      case 4:
        leds[selection] = WHITE;
        break;
      case 5:
        leds[selection] = YELLOW;
        break;
      }
    }
  }

  FastLED.show();
}

void loop() {
  delay(300);
  rubixRot(random(0, 7), random(0, 1));
  if (memcmp(leds, solution, sizeof(CRGB) * NUM_LEDS) == 0) {
    while(true) {
      setColor({255, 255, 255}, (CRGB) 0x0, leds);
      delay(200);
      setColor({255, 255, 255}, GREEN, leds);
      delay(200);
    }
  }
}

void rubixRot(byte side, bool dir){
  rotate(side, dir, 2, leds);
  LEDSelect origin = {side, 0, 0};
  getNeighborLED(&origin, NORTH, &origin);
  if(dir == 0){
    new_rotaterot(origin, METAROTTODIR[side], 3, leds);
  }else{
    for(byte i = 0; i < 3; i++){
      rubixRot(side,0);
    }
  }
}
