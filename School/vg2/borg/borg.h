#ifndef borg_h
#define borg_h

#include "Arduino.h"
#include <FastLED.h>

struct LEDSelect {
	byte side;
	byte column;
	byte row;
};

// Decodes side, column, row into n LED
int decodeLED(LEDSelect selection);
void encodeLED(int n, LEDSelect* Result);

/*
** Set Color
** Takes a led selection,
** The last two propertries can be 255, meaning no information
** the property that is 255 will be inclusively filled with the CRGB color
*/
bool setColor(LEDSelect selection, CRGB color, CRGB* leds);
// Sets every color that isn't black
bool updateColors(LEDSelect selection, CRGB* leds);
// Mirrors one side to every other side
bool mirror(byte side, CRGB* leds);
//Prints large X in a given color
void printError(CRGB color, CRGB* leds);




int decodeLED(LEDSelect selection) {
	return 9 * selection.side + 3 * selection.row + selection.column;
}

void encodeLED(int n, LEDSelect* Result) {
	Result->side = n / 9;
	Result->column = n % 9 / 3;
	Result->row = n % 9 % 3;
}

bool setColor(LEDSelect selection, CRGB color, CRGB* leds) {
	if (selection.side == 255) {
		return false;
	}
	if (selection.column == 255 && selection.row == 255) {
		for (byte n = 0; n < 9; n++) {
			leds[selection.side * 9 + n] = color;
		}
		return true;
	}
	else if (selection.column == 255 && selection.row != 255) {
		for (byte n = 0; n < 3; n++) {
			leds[decodeLED({ selection.side, n, selection.row })] = color;
		}
		return true;
	}
	else if (selection.column != 255 && selection.row == 255) {
		for (byte n = 0; n < 3; n++) {
			leds[decodeLED({ selection.side, selection.column, n })] = color;
		}
		return true;
	}
	else if (selection.column != 255 && selection.row != 255) {
		leds[decodeLED(selection)] = color;
		return true;
	}
	else {
		return false;
	}
}


bool updateColors(LEDSelect selection, CRGB color, CRGB* leds) {
	if (selection.side == 255) {
		return false;
	}
	
	
	if (selection.column == 255 && selection.row == 255) {
		for (int n = 0; n < 9; n++) {
			CRGB* led = &leds[selection.side * 9 + n];
			if (*led != (CRGB) 0x000000) {
				*led = color;
			}
		}
		return true;
	}
	else if (selection.column == 255 && selection.row != 255) {
		for (int n = 0; n < 3; n++) {
			CRGB* led = &leds[decodeLED({ selection.side, n, selection.row })];
			if (*led != (CRGB)0x000000) {
				*led = color;
			}
		}
		return true;
	}
	else if (selection.column != 255 && selection.row == 255) {
		for (int n = 0; n < 3; n++) {
			CRGB* led = &leds[decodeLED({ selection.side, selection.column, n })];
			if (*led != (CRGB) 0x000000) {
				*led = color;
			}
		}
		return true;
	}
	else if (selection.column != 255 && selection.row != 255) {
		CRGB* led = &leds[decodeLED(selection)];
		if (*led != (CRGB) 0x000000) {
			*led = color;
		}
		return true;
	}
	else {
		return false;
	}
}

bool mirror(byte side, CRGB* leds) {
	/*TODO: figure out memory structure, 
		copy the nine leds to the the different memory parts, so it the text is displayed on all sides.
		should probably use some form of modulo
	*/
	for(int i = 0; i < sizeof(leds) / sizeof(CRGB); i+=9) {
		memcpy(&leds[i], &leds[decodeLED({side, 0, 0})], sizeof(CRGB) * 9);
	}
}

void printError(CRGB color, CRGB* leds) {
	setColor({0, 255, 255}, (CRGB) color, leds);
	setColor({0, 0, 1}, (CRGB) 0, leds);
	setColor({0, 1, 0}, (CRGB) 0, leds);
	setColor({0, 1, 2}, (CRGB) 0, leds);
	setColor({0, 2, 1}, (CRGB) 0, leds);
	mirror(0, leds);
}

#endif
