#ifndef __ROTOR_H__
#define __ROTOR_H__

#include <stdio.h>
#include "constants.h"

typedef struct {
	int rotorID;
	int map[LETTER_COUNT];
	int turnoverPosition;
	int positionOffset;
} Rotor;

void rotorInit(Rotor *rotor, int rotorNumber);
void reflectorInit(Rotor *rotor);
int rotorApplyForward(Rotor *rotor, int value);
int rotorApplyBackward(Rotor *rotor, int value);
void rotorPrint(Rotor *rotor);
int rotorRotate(Rotor *rotor);

#endif // #ifndef __ROTOR_H__
