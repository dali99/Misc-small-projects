#ifndef borg_h
#define borg_h

#include "Arduino.h"
#include <FastLED.h>

struct LEDSelect {
	byte side;
	byte column;
	byte row;
};

// Poor man's enumarator
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// ROTTODIR
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define CLOCKW 4 // Clockwise
#define ACLOCKW 5 // Anticlockwise - Actually a word in English (AU) according to wiktionary.
// Besides, CCLOCKW looked stupid

// Directions[sides, directions]
// 0 - North; 1 - East; 2 - South, 3 - West
byte DIRECTIONS[6][4];
byte ROTTODIR[6][6];

// Initializing mapping for directions
void initMap(void);
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
//Gets neighbor led with sky directions, nice for single screen movement, but can also handle cross screen.
void getNeighborLED(LEDSelect* origin, byte origin_dir, LEDSelect* Result);
// Gets neighbor led with set directions in reference to side 0, lets you move in one direction with one vector.
void getRotNeighborLED(LEDSelect* origin, byte rot, LEDSelect* Result);
//
void translate(LEDSelect src, LEDSelect dst, CRGB* leds);
// Rotates a side, in given direction, 0 - Clockwise, 1 - Anticlockwise
void rotate(byte side, bool dir, byte n, CRGB* leds);

void initMap(void)
{
	DIRECTIONS[0][NORTH] = 4;
	DIRECTIONS[0][EAST] = 1;
	DIRECTIONS[0][SOUTH] = 5;
	DIRECTIONS[0][WEST] = 3;

	DIRECTIONS[1][NORTH] = 4;
	DIRECTIONS[1][EAST] = 2;
	DIRECTIONS[1][SOUTH] = 5;
	DIRECTIONS[1][WEST] = 0;

	DIRECTIONS[2][NORTH] = 4;
	DIRECTIONS[2][EAST] = 3;
	DIRECTIONS[2][SOUTH] = 5;
	DIRECTIONS[2][WEST] = 1;

	DIRECTIONS[3][NORTH] = 4;
	DIRECTIONS[3][EAST] = 0;
	DIRECTIONS[3][SOUTH] = 5;
	DIRECTIONS[3][WEST] = 2;

	DIRECTIONS[4][NORTH] = 0;
	DIRECTIONS[4][EAST] = 3;
	DIRECTIONS[4][SOUTH] = 2;
	DIRECTIONS[4][WEST] = 1;

	DIRECTIONS[5][NORTH] = 2;
	DIRECTIONS[5][EAST] = 3;
	DIRECTIONS[5][SOUTH] = 0;
	DIRECTIONS[5][WEST] = 1;


	ROTTODIR[0][UP] = NORTH;
	ROTTODIR[0][RIGHT] = EAST;
	ROTTODIR[0][DOWN] = SOUTH;
	ROTTODIR[0][LEFT] = WEST;
	ROTTODIR[0][CLOCKW] = 255;
	ROTTODIR[0][ACLOCKW] = 255;

	ROTTODIR[1][UP] = 255;
	ROTTODIR[1][RIGHT] = EAST;
	ROTTODIR[1][DOWN] = 255;
	ROTTODIR[1][LEFT] = WEST;
	ROTTODIR[1][CLOCKW] = SOUTH;
	ROTTODIR[1][ACLOCKW] = NORTH;

	ROTTODIR[2][UP] = SOUTH;
	ROTTODIR[2][RIGHT] = EAST;
	ROTTODIR[2][DOWN] = NORTH;
	ROTTODIR[2][LEFT] = WEST;
	ROTTODIR[2][CLOCKW] = 255;
	ROTTODIR[2][ACLOCKW] = 255;

	ROTTODIR[3][UP] = 255;
	ROTTODIR[3][RIGHT] = EAST;
	ROTTODIR[3][DOWN] = 255;
	ROTTODIR[3][LEFT] = WEST;
	ROTTODIR[3][CLOCKW] = NORTH;
	ROTTODIR[3][ACLOCKW] = SOUTH;

	ROTTODIR[4][UP] = SOUTH;
	ROTTODIR[4][RIGHT] = 255;
	ROTTODIR[4][DOWN] = NORTH;
	ROTTODIR[4][LEFT] = 255;
	ROTTODIR[4][CLOCKW] = EAST;
	ROTTODIR[4][ACLOCKW] = WEST;

	ROTTODIR[5][UP] = SOUTH;
	ROTTODIR[5][RIGHT] = 255;
	ROTTODIR[5][DOWN] = NORTH;
	ROTTODIR[5][LEFT] = 255;
	ROTTODIR[5][CLOCKW] = WEST;
	ROTTODIR[5][ACLOCKW] = EAST;

	
}

int decodeLED(LEDSelect selection)
{
	return 9 * selection.side + 3 * selection.row + selection.column;
}

void encodeLED(int n, LEDSelect* Result)
{
	Result->side = n / 9;
	Result->column = n % 9 / 3;
	Result->row = n % 9 % 3;
}


void forceMove(LEDSelect* selection, byte direction)
{
	switch (direction) {
	case 0:
		selection->row--;
		break;
	case 1:
		selection->column++;
		break;
	case 2:
		selection->row++;
		break;
	case 3:
		selection->column--;
		break;
	}
}

// Takes a single LED and find its neighbor, based on direction
void getNeighborLED(LEDSelect* origin, byte origin_dir, LEDSelect* Result)
{

	byte row = origin->row;
	byte column = origin->column;
	byte side = origin->side;

	*Result = *origin;

	if(column == 255 && row == 255){
		Result->side = DIRECTIONS[side][origin_dir];
		return;
	}
	else if(column != 255 && row == 255){
		if(origin_dir == NORTH || origin_dir == SOUTH){
			Result->side = DIRECTIONS[side][origin_dir];
			return;
		}
		Result->row = 1;
		getNeighborLED(Result, origin_dir, Result);
		Result->row = 255;
		return;
	}
	else if(column == 255 && row != 255){
		if(origin_dir == WEST || origin_dir == EAST){
			Result->side = DIRECTIONS[side][origin_dir];
			return;
		}
		Result->column = 1;
		getNeighborLED(Result, origin_dir, Result);
		Result->column = 255;
		return;
	}

	// Case midt LED
	if (column == 1 && row == 1) {
		forceMove(Result, origin_dir);
		return;
	}


	// Case edges, corners
	if (row == 0 && origin_dir == SOUTH) {
		Result->row++;
		return;
	}
	if (column == 2 && origin_dir == WEST) {
		Result->column--;
		return;
	}
	if (row == 2 && origin_dir == NORTH) {
		Result->row--;
		return;
	}
	if (column == 0 && origin_dir == EAST) {
		Result->column++;
		return;
	}
	
	// Cases midten av edges
	if (row == 0 && column == 1 && origin_dir != NORTH) {
		forceMove(Result, origin_dir);
		return;
	}
	if (column == 2 && row == 1 && origin_dir != EAST) {
		forceMove(Result, origin_dir);
		return;
	}
	if (row == 2 && column == 1 && origin_dir != SOUTH) {
		forceMove(Result, origin_dir);
		return;
	}
	if (column == 0 && row == 1 && origin_dir != WEST) {
		forceMove(Result, origin_dir);
		return;
	}

	
	Result->side = DIRECTIONS[side][origin_dir];
	byte edge;
	for (edge = 0; edge < 4; edge++) {
		if (DIRECTIONS[Result->side][edge] == side)
			break;
	}

	switch (edge) {
	case NORTH:
		Result->row = 0;
		break;
	case EAST:
		Result->column = 2;
		break;
	case SOUTH:
		Result->row = 2;
		break;
	case WEST:
		Result->column = 0;
		break;
	}

	if (column == 1) // if middle pixel, no one has to get hurt ^^
		return;


	if ((side == 0 && (origin_dir == NORTH || origin_dir == SOUTH))
		|| (side == 4 && origin_dir == NORTH)
		|| (side == 5 && origin_dir == SOUTH)) {
			(column == 0) ? Result->column = 2 : Result->column = 0; // Sets edge to opposite
			return;
	}
	if  ((side == 1 && origin_dir == NORTH)
		|| (side == 3 && origin_dir == SOUTH)
		|| (side == 4 && origin_dir == WEST) 
		|| (side == 5 && origin_dir == EAST)) {
			Result->column = row;
			Result->row = column;
			return;
	}

	if (side == 1 && origin_dir == SOUTH
		|| side == 5 && origin_dir == WEST
		|| side == 4 && origin_dir == EAST
		|| side == 3 && origin_dir == NORTH) {
			if (column == row) {
				if (column == 0) {
					Result->column = 2;
					Result->row = 2;
				}
				else {
					Result->column = 0;
					Result->row = 0;
				}
			}
	}	
}

void getRotNeighborLED(LEDSelect* origin, byte rot, LEDSelect* Result)
{
	byte direction = ROTTODIR[origin->side][rot];
	if (direction == 255)
		return;

	getNeighborLED(origin, direction, Result);
}

void translate(LEDSelect src, LEDSelect dst, CRGB* leds){
	byte side = src.side;
	byte column = src.column;
	byte row = src.row;

	if(column == 255 && row == 255 &&
	   dst.column == 255 && dst.row == 255){
		src.column = 0;
		src.row = 0;

		dst.column = 0;
		dst.row = 0;

		for(int i = 0; i < 9; i++){
			leds[decodeLED(dst) + i] = leds[decodeLED(src) + i];
		}
		return;
	}
	else if(column != 255 && row == 255 && 
			dst.column != 255 && dst.row == 255){
		src.row = 0;
		dst.row = 0;

		for(int i = 0; i < 9; i += 3){
			leds[decodeLED(dst) + i] = leds[decodeLED(src) + i];
		}
		return;
	}
	else if(column == 255 && row != 255 && dst.column == 255 && dst.row != 255){
		src.column = 0;
		dst.column = 0;

		for(int i = 0; i < 3; i++){
			leds[decodeLED(dst) + i] = leds[decodeLED(src) + i];
		}
		return;
	}

	leds[decodeLED(dst)] = leds[decodeLED(src)];
}

void rotate(byte side, bool direction, byte n, CRGB* leds)
{

	firstLED = decodeLED({selection.side, 0, 0});
	byte cyclus[8] = {0, 3, 6, 7, 8, 5, 2, 1};
	for (byte i = 0; i < n; i++)
	{
		if (direction == 0) {
			CRGB Saved = leds[cyclus[0] + firstLED];
			for(byte j = 0; j < 8; j++) {
				leds[cyclus[j] + firstLED] = leds[cyclus[j + 1] + firstLED]; 
			}
			leds[cyclus[7] + firstLED] = Saved;
		}
		else {
			CRGB Saved = leds[cyclus[0] + firstLED];
			for(byte j = 7; j > 0; j--) {
				leds[cyclus[j] + firstLED] = leds[cyclus[j - 1] + firstLED]; 
			}
			leds[cyclus[1] + firstLED] = Saved;
		}
	}
		
}

bool setColor(LEDSelect selection, CRGB color, CRGB* leds)
{
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


bool updateColors(LEDSelect selection, CRGB color, CRGB* leds)
{
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

bool mirror(byte side, CRGB* leds)
{
	/*TODO: figure out memory structure, 
		copy the nine leds to the the different memory parts, so it the text is displayed on all sides.
		should probably use some form of modulo
	*/
	for(int i = 0; i < sizeof(leds) / sizeof(CRGB); i+=9) {
		memcpy(&leds[i], &leds[decodeLED({side, 0, 0})], sizeof(CRGB) * 9);
	}
}

void printError(CRGB color, CRGB* leds)
{
	setColor({0, 255, 255}, (CRGB) color, leds);
	setColor({0, 0, 1}, (CRGB) 0, leds);
	setColor({0, 1, 0}, (CRGB) 0, leds);
	setColor({0, 1, 2}, (CRGB) 0, leds);
	setColor({0, 2, 1}, (CRGB) 0, leds);
	mirror(0, leds);
}

#endif
