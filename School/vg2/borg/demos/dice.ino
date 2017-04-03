#include <FastLED.h>
#include <borg.h>

#define NUM_LEDS 54
#define DATA_PIN 7
#define COLOR (CRGB) 0x00FF00

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
 
  randomSeed(analogRead(0));
}

void loop()
{
  roll(random(1,7), 0, leds);
  mirror(0, leds);
  FastLED.show();
  delay(1500);
}


void roll(byte n, byte side, CRGB* leds) {
  setColor({side, 255, 255}, (CRGB) 0, leds);
  switch (n) {
    case 1:
      setColor({side,1,1}, COLOR, leds);
      break;
    case 2:
      setColor({side,2,0}, COLOR, leds);
      setColor({side,0,2}, COLOR, leds);
      break;
    case 3:
      setColor({side,2,0}, COLOR, leds);
      setColor({side,1,1}, COLOR, leds);
      setColor({side,0,2}, COLOR, leds);
      break;
    case 4:
      setColor({side,0,0}, COLOR, leds);
      setColor({side,2,0}, COLOR, leds);
      setColor({side,0,2}, COLOR, leds);
      setColor({side,2,2}, COLOR, leds);
      break;
    case 5:
      setColor({side,0,0}, COLOR, leds);
      setColor({side,2,0}, COLOR, leds);
      setColor({side,1,1}, COLOR, leds);
      setColor({side,0,2}, COLOR, leds);
      setColor({side,2,2}, COLOR, leds);
      break;
    case 6:
      setColor({side, 0, 255}, COLOR, leds);
      setColor({side, 2, 255}, COLOR, leds);
      break;
   default:
      printError((CRGB) 0xFF0000, leds);
      break;
  }
}
