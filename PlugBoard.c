#include "PlugBoard.h"

void plugBoardInit(PlugBoard *plugBoard)
{
    plugBoard->plugsUsed = 0;
    for(int index = 0; index < LETTER_COUNT; ++index) {
        plugBoard->plugPairs[index] = index;
    }
}

void plugBoardSet(PlugBoard *plugBoard, char char1, char char2)
{
    if(plugBoard->plugsUsed < 10) {
        int val1 = char1 - 'A';
        int val2 = char2 - 'A';

        plugBoard->plugPairs[val1] = val2;
        plugBoard->plugPairs[val2] = val1;

        ++(plugBoard->plugsUsed); // plugsUsed = plugsUsed + 1;
    } else {
        printf("ERROR: You've already used all the plugs!\n");
    }
}

int plugBoardApply(PlugBoard *plugBoard, int value)
{
    int result = -1;
    if(0 <= value && value < LETTER_COUNT) {
        result = plugBoard->plugPairs[value];
    } else {
        printf("ERROR: Invalid plug board input: %d\n", value);
    }
    return result;
}

void plugBoardPrint(PlugBoard *plugBoard)
{
    printf("Plug Board:\n");
    for(int index = 0; index < LETTER_COUNT; ++index) {
        int value = plugBoard->plugPairs[index];
        char inputChar = index + 'A';
        char outputChar = value + 'A';
        printf("    %c => %c\n", inputChar, outputChar);
    }
}
