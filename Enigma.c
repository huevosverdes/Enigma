#include "Enigma.h"

void enigmaInit(Enigma *enigma)
{
	plugBoardInit(&(enigma->plugBoard));
	reflectorInit(&(enigma->reflector));
}

int enigmaSetRotor(Enigma *enigma, int rotorPosition, int rotorNum, char rotorOffset)
{
    int result = 1;

    switch(rotorPosition) {
    case 1:
        rotorInit(&(enigma->rotor1), rotorNum);
        enigma->rotor1.positionOffset = rotorOffset - 'A';
        break;
    case 2:
        rotorInit(&(enigma->rotor2), rotorNum);
        enigma->rotor2.positionOffset = rotorOffset - 'A';
        break;
    case 3:
        rotorInit(&(enigma->rotor3), rotorNum);
        enigma->rotor3.positionOffset = rotorOffset - 'A';
        break;
    default:
        printf("ERROR: Invalid Rotor position \"%d\"", rotorPosition);
        result = 0;
        break;
    }

    return result;
}

void enigmaPlug(Enigma *enigma, char char1, char char2)
{
	plugBoardSet(&(enigma->plugBoard), char1, char2);
}

void enigmaPrint(Enigma *enigma)
{
	printf("Rotor 1: %d(%c)\n", enigma->rotor1.rotorID, enigma->rotor1.positionOffset + 'A');
	printf("Rotor 2: %d(%c)\n", enigma->rotor2.rotorID, enigma->rotor2.positionOffset + 'A');
	printf("Rotor 3: %d(%c)\n", enigma->rotor3.rotorID, enigma->rotor3.positionOffset + 'A');
	plugBoardPrint(&(enigma->plugBoard));
}

char enigmaApplyChar(Enigma *enigma, char c)
{
	int value = c - 'A';
	value = plugBoardApply(&(enigma->plugBoard), value);
	value = rotorApplyForward(&(enigma->rotor1), value);
	value = rotorApplyForward(&(enigma->rotor2), value);
	value = rotorApplyForward(&(enigma->rotor3), value);
	value = rotorApplyForward(&(enigma->reflector), value);
	value = rotorApplyBackward(&(enigma->rotor3), value);
	value = rotorApplyBackward(&(enigma->rotor2), value);
	value = rotorApplyBackward(&(enigma->rotor1), value);
	value = plugBoardApply(&(enigma->plugBoard), value);

	if(rotorRotate(&(enigma->rotor1))) {
		if(rotorRotate(&(enigma->rotor2))) {
			rotorRotate(&(enigma->rotor3));
		}
	}

	return value + 'A';
}

void enigmaApplyStr(Enigma *enigma, const char *msg)
{
	for(size_t index = 0; index < strlen(msg); ++index) {
		char c = msg[index];
		if('A' <= c && c <= 'Z') {
			char o = enigmaApplyChar(enigma, c);
			printf("%c", o);
		}

		if('a' <= c && c <= 'z') {
			char o = enigmaApplyChar(enigma, c - 'a' + 'A');
			printf("%c", o);
		}
	}
	printf("\n");
}
