#include <stdio.h>

#define DICEN 5

#define RUMBLE 2
#define DC1LCK 3
#define DC2LCK 4
#define DC3LCK 5
#define DC4LCK 6
#define DC5LCK 7

#define SHCLK 8
#define DCSR 9

int toDice(int n);
unsigned long int shift(int* numbers);

uint8_t dicerolls[DICEN];

void setup() {
  randomSeed(analougeRead(0));

  pinMode(RUMBLE, INPUT);
  pinMode(DC1LCK, INPUT);
  pinMode(DC2LCK, INPUT);
  pinMode(DC3LCK, INPUT);
  pinMode(DC4LCK, INPUT);
  pinMode(DC5LCK, INPUT);

  pinMode(SHCLK, OUTPUT);
  pinMode(DCSR, OUTPUT);

  for (int i = 0; i < DICEN; i++) {
    dicerolls[i] = 0;
  }
}

void loop() {
  if (digitalRead(RUMBLE) == HIGH) {
    if (digitalRead(DC1LCK) == LOW) {
      dicerolls[0] = random(1, 7);
    }
    if (digitalRead(DC2LCK) == LOW) {
      dicerolls[1] = random(1, 7);
    }
    if (digitalRead(DC3LCK) == LOW) {
      dicerolls[2] = random(1, 7);
    }
    if (digitalRead(DC4LCK) == LOW) {
      dicerolls[3] = random(1, 7);
    }
    if (digitalRead(DC5LCK) == LOW) {
      dicerolls[4] = random(1, 7);
    }
    unsigned long int result = shift(dicerolls)
    /*shiftOut(result >> 16);
    shiftOut(result >> 8);
    shiftOut(result);*/
  }
}



/*     A | B | C | D
   1 = 1 | 0 | 0 | 0 0x8
   2 = 0 | 0 | 1 | 0 0x2
   3 = 1 | 0 | 1 | 0 0xA
   4 = 0 | 1 | 1 | 0 0x6
   5 = 1 | 1 | 1 | 0 0xE
   6 = 0 | 1 | 1 | 1 0x7 */
int toDice(int n) {
  // anything out of bounds turns the dice off
  // Should probably use 0 for that though
  
  switch (n) {
    case 1:
      return 0x8;
    case 2:
      return 0x2;
    case 3:
      return 0xA;
    case 4:
      return 0x6;
    case 5:
      return 0xE;
    case 6:
      return 0x7;
    default:
      return 0x0;
  }
}

/* Combines DICEN numbers in a 32 bit int
   Change data type to a long long if DICEN > 8 */
unsigned long int shift(int* numbers) {
  
  unsigned long int shiftn = 0; /* set entire 32 bit to 0 */
  
  for (int i = 0; i < DICEN - 1; i++) /* For all but the last pass */ {
    shiftn = shiftn | toDice(numbers[i]); /* OR 4 bits to the int, writes it to the least significant portion */
    shiftn = shiftn << 4; /* shift the 4 bits to the left, making space for another 4 bit */
  }
  shiftn = shiftn | toDice(numbers[DICEN - 1]); /* For the last pass, only OR */
  
  return shiftn; /* End result is a number representing your data outputs for all DICEN */
}
