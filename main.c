#include <stdio.h>
#include <string.h>

#include "Enigma.h"

int setEnigmaRotor(Enigma *enigma, int rotorPosition, const char *rotorArg, int rotorArgIndex, char *offsetArg, int offsetArgIndex);
int addPlug(Enigma *enigma, const char *arg, int argIndex);
int rotorNumberFromArg(const char *arg, int argIndex);
void printHelp();

int main(int argc, char **argv)
{
    if(argc != 18) {
        printHelp();
    } else {
        int status = 1;
        Enigma enigma;
        enigmaInit(&enigma);

        status &= setEnigmaRotor(&enigma, 1, argv[1], 1, argv[2], 2);
        status &= setEnigmaRotor(&enigma, 2, argv[3], 3, argv[4], 4);
        status &= setEnigmaRotor(&enigma, 3, argv[5], 5, argv[6], 6);

        status &= addPlug(&enigma, argv[7], 7);
        status &= addPlug(&enigma, argv[8], 8);
        status &= addPlug(&enigma, argv[9], 9);
        status &= addPlug(&enigma, argv[10], 10);
        status &= addPlug(&enigma, argv[11], 11);
        status &= addPlug(&enigma, argv[12], 12);
        status &= addPlug(&enigma, argv[13], 13);
        status &= addPlug(&enigma, argv[14], 14);
        status &= addPlug(&enigma, argv[15], 15);
        status &= addPlug(&enigma, argv[16], 16);

        if(status) {
            enigmaApplyStr(&enigma, argv[17]);
        } else {
            printHelp();
        }
    }

    return 0;
}

int setEnigmaRotor(Enigma *enigma, int rotorPosition, const char *rotorArg, int rotorArgIndex, char *offsetArg, int offsetArgIndex)
{
    int result = 1;

    int rotor = rotorNumberFromArg(rotorArg, rotorArgIndex);
    if(rotor <= 0) {
        printf("ERROR: Invalid Rotor \"%s\" at argument #%d\n", rotorArg, rotorArgIndex);
        result = 0;
    }

    char rotorOffset = offsetArg[0];
    if(!(strlen(offsetArg) == 1 && 'A' <= rotorOffset && rotorOffset <= 'Z')) {
        printf("ERROR: Invalid Rotor offset \"%s\" at argument #%d\n", offsetArg, offsetArgIndex);
        result = 0;
    }

    return result && enigmaSetRotor(enigma, rotorPosition, rotor, rotorOffset);
}

int addPlug(Enigma *enigma, const char *arg, int argIndex)
{
    if(strlen(arg) == 2 &&
       'A' <= arg[0] && arg[0] <= 'Z' &&
       'A' <= arg[1] && arg[1] <= 'Z' &&
       arg[0] != arg[1]) {
        enigmaPlug(enigma, arg[0], arg[1]);
        return 1;
    }

    printf("ERROR: Invalid Plug \"%s\" at argument #%d\n", arg, argIndex);
    return 0;
}

int rotorNumberFromArg(const char *arg, int argIndex)
{
    int result = -1;

    if(strcmp(arg, "I") == 0) result = 1;
    if(strcmp(arg, "II") == 0) result = 2;
    if(strcmp(arg, "III") == 0) result = 3;
    if(strcmp(arg, "IV") == 0) result = 4;
    if(strcmp(arg, "V") == 0) result = 5;

    return result;
}

void printHelp()
{
    printf("usage: Enigma.exe ROTOR1 CHAR1 ROTOR2 CHAR2 ROTOR3 CHAR3 PLUG0 PLUG1 PLUG2 PLUG3 PLUG4 PLUG5 PLUG6 PLUG7 PLUG8 PLUG9 MESSAGE\n");
    printf("  - ROTOR must be a Roman Numeral from 1 to 5: One of {I, II, III, IV, V}\n");
    printf("  - CHAR is an offset on the ROTOR and must be an uppercase letter in the English alphabet: One of A-Z\n");
    printf("  - PLUG is a pair of different uppercase letters in the English alphabet: e.g. AB or CD \n");
    printf("  - MESSAGE is a string in quotes, not case sensitive. Invalid characters will be skipped so feel free to use punctuation and so on.\n");
    printf("Example: Enigma.exe I P V K III Z SZ GT DV KU FO MY EW JN IX LQ \"YSTFQHIVEUBLNEZSFLFXFHXIEGNUZRVKUMVXMUZSVGHCFQVWEZCBFPT\"\n\n");
}
