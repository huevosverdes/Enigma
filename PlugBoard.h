#ifndef __PLUG_BOARD_H__
#define __PLUG_BOARD_H__

#include <stdio.h>
#include "constants.h"

typedef struct {
    int plugPairs[LETTER_COUNT];
    int plugsUsed;
} PlugBoard;

void plugBoardInit(PlugBoard *plugBoard);
void plugBoardSet(PlugBoard *plugBoard, char char1, char char2);
int plugBoardApply(PlugBoard *plugBoard, int value);
void plugBoardPrint(PlugBoard *plugBoard);

#endif // #ifndef __PLUG_BOARD_H__
