#ifndef __ENIGMA_H__
#define __ENIGMA_H__

#include <stdio.h>
#include <string.h>

#include "PlugBoard.h"
#include "Rotor.h"

typedef struct {
	PlugBoard plugBoard;
	Rotor rotor1;
	Rotor rotor2;
	Rotor rotor3;
	Rotor reflector;
} Enigma;

void enigmaInit(Enigma *enigma);
int enigmaSetRotor(Enigma *enigma, int rotorPosition, int rotorNum, char rotorOffset);
void enigmaPlug(Enigma *enigma, char char1, char char2);
void enigmaPrint(Enigma *enigma);
char enigmaApplyChar(Enigma *enigma, char c);
void enigmaApplyStr(Enigma *enigma, const char *msg);

#endif // #ifndef __ENIGMA_H__
