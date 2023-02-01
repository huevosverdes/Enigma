#include "Rotor.h"

#define ROTOR_COUNT 5

const char REFLECTOR_MAP[] = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
const char ROTOR_MAPS[ROTOR_COUNT][LETTER_COUNT+1] = {
	"PEZUOHXSCVFMTBGLRINQJWAYDK",
	"ZOUESYDKFWPCIQXHMVBLGNJRAT",
	"EHRVXGAOBQUSIMZFLYNWKTPDJC",
	"IMETCGFRAYSQBZXWLHKDVUPOJN",
	"QWERTZUIOASDFGHJKPYXCVBNML"
};
const char ROTOR_TURNOVER_POSITIONS[ROTOR_COUNT] = { 'R', 'F', 'W', 'K', 'A' };

void rotorInit(Rotor *rotor, int rotorNumber)
{
	if(1 <= rotorNumber && rotorNumber <= ROTOR_COUNT) {
		int rotorIndex = rotorNumber - 1;

		rotor->rotorID = rotorNumber;
		rotor->turnoverPosition = ROTOR_TURNOVER_POSITIONS[rotorIndex];
		rotor->positionOffset = 0;

		for(int index = 0; index < LETTER_COUNT; ++index) {
			int output = ROTOR_MAPS[rotorIndex][index] - 'A';
			rotor->map[index] = output;
		}
	} else {
		rotor->rotorID = -1;
		printf("ERROR: Invalid Rotor Number \"%d\"\n", rotorNumber);
	}
}

void reflectorInit(Rotor *rotor)
{
	rotor->rotorID = 0;
	rotor->turnoverPosition = 0;
	rotor->positionOffset = 0;
	for(int index = 0; index < LETTER_COUNT; ++index) {
		int output = REFLECTOR_MAP[index] - 'A';
		rotor->map[index] = output;
	}
}

int rotorApplyForward(Rotor *rotor, int value)
{
	int result = -1;
	if(0 <= value && value < LETTER_COUNT) {
		int rotatedV = value + rotor->positionOffset;
		if(rotatedV >= LETTER_COUNT) {
			rotatedV -= LETTER_COUNT;
		}
		result = rotor->map[rotatedV];
	} else {
		printf("ERROR: Invalid rotor input: %d", value);
	}
	return result;
}

int rotorApplyBackward(Rotor *rotor, int value)
{
	int result = -1;
	if(0 <= value && value < LETTER_COUNT) {
		for(int index = 0; index < LETTER_COUNT; ++index) {
			if(rotor->map[index] == value) {
				result = index;
				break;
			}
		}
		result = result - rotor->positionOffset;
		if(0 > result) {
			result += LETTER_COUNT;
		}
	} else {
		printf("ERROR: Invalid rotor input: %d", value);
	}
	return result;
}

void rotorPrint(Rotor *rotor)
{
	printf("Rotor:\n");
	for(int index = 0; index < LETTER_COUNT; ++index) {
		int value = rotor->map[index];
		char inputChar = index + 'A';
		char outputChar = value + 'A';
		printf("    %c => %c\n", inputChar, outputChar);
	}
}

int rotorRotate(Rotor *rotor)
{
	int result = 0;

	++(rotor->positionOffset);
	if(rotor->positionOffset >= LETTER_COUNT) {
		rotor->positionOffset = 0;
	}
	if(rotor->positionOffset == rotor->turnoverPosition) {
		result = 1;
	}

	return result;
}
