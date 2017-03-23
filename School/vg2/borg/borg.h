#ifndef borg_h
#define borg_h

#include "Arduino.h"
#include <FastLED.h>

struct LEDSelect {
	byte side;
	byte column;
	byte row;
};

// Directions[sides, directions]
// 0 - North; 1 - East; 2 - South, 3 - West
byte DIRECTIONS[6][4];

DIRECTIONS[0][0] = 4;
DIRECTIONS[0][1] = 1;
DIRECTIONS[0][2] = 5;
DIRECTIONS[0][3] = 3;

DIRECTIONS[1][0] = 4;
DIRECTIONS[1][1] = 2;
DIRECTIONS[1][2] = 5;
DIRECTIONS[1][3] = 0;

DIRECTIONS[2][0] = 4;
DIRECTIONS[2][1] = 3;
DIRECTIONS[2][2] = 5;
DIRECTIONS[2][3] = 1;

DIRECTIONS[3][0] = 4;
DIRECTIONS[3][1] = 0;
DIRECTIONS[3][2] = 5;
DIRECTIONS[3][3] = 2;

DIRECTIONS[4][0] = 0;
DIRECTIONS[4][1] = 3;
DIRECTIONS[4][2] = 2;
DIRECTIONS[4][3] = 1;

DIRECTIONS[5][0] = 2;
DIRECTIONS[5][1] = 3;
DIRECTIONS[5][2] = 0;
DIRECTIONS[5][3] = 1;

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


void forceMove(LEDSelect* selection, byte direction) {
	switch (origin_dir) {
		case 0:
			selection->row--;
			break;
		case 1:
			selection->column++;
			break;
		case 2:
			selection->row++:
			break;
		case 3:
			selection->column--;
			break;
	}
	return;
}

// Takes a single LED and find its neighbor, based on direction
void getNeighborLED(LEDSelect* origin, byte origin_dir, LEDSelect* Result) {
	byte row = origin->row;
	byte column = origin->column;

	*Result = *origin;

	// Case midt LED
	if (column == 1 && row == 1) {
		forceMove(Result, origin_dir);
		return;
	}


	// Case edges, corners
	if (row == 0 && origin_dir == 2) {
		Result->row++;
		return;
	}
	if (column == 2 && origin_dir == 3) {
		Result->column--;
		return;
	}
	if (row == 2 && origin_dir == 0) {
		Result->row--;
		return;
	}
	if (column == 0 && origin_dir == 1) {
		Result->column++;
		return;
	}
	
	// Cases midten av edges
	if (row == 0 && column == 1 && origin_dir != 0) {
		forceMove(Result, origin_dir);
		return;
	}
	if (column == 2 && row == 1 && origin_dir != 1) {
		forceMove(Result, origin_dir);
		return;
	}
	if (row == 2 && column == 1 && origin_dir != 2) {
		forceMove(Result, origin_dir);
		return;
	}
	if (column == 0 && row == 1 && origin_dir != 3) {
		forceMove(Result, origin_dir);
		return;
	}

	Result->side = DIRECTIONS[origin->side][origin_dir];
	byte edge;
	for (edge = 0; edge < 4; edge++) {
		if (DIRECTIONS[Result->side][edge] == origin->side) {
			break;
		}
	}
	switch (edge) {
		case 0:
			Result->row = 0;
			break;
		case 1:
			Result->column = 2;
			break;
		case 2:
			Result->row = 2;
			break;
		case 3:
			Result->column = 0;
			break;
	}

	if (column == 1) {
		return;
	}

	if ((side == 0 && (origin_dir == 0 || origin_dir == 2)) || (side == 4 && origin_dir == 0)) {
		(column == 0) ? Result->column = 2 : Result->column = 0;
	}
	if ((side == 1 && origin_dir == 0) || (side == 3 && origin_dir == 2)
		||(side == 4 && origin_dir == 3) || (side == 5 && origin_dir == 1)) {
		Result->column = row;
		Result->row = column;
	}
	// Wrong!!
	if ((side == 1 && origin_dir == 2) || (side == 3 && origin_dir == 0)) {
		Result->column = 0;
		(column == 0) ? Result->row = 2 : Result->row = 0;
	}
	if ((side == 4 && origin_dir == 1) || (side == 5 && origin_dir == 3)) {
		Result->row = 2;
		(row == 0) ? Result->column = 2 : Result->column = 0;
	}
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
