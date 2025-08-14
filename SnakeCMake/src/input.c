#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "input.h"
#include "globals.h"


static char key = '\0';

void Input_readKey() {
    // Check for key press
    if (_kbhit()) {
        char ch = _getch();
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT)) {// KEY_LEFT and KEY_RIGHT are in globals.h
            key = ch;
        }
    }
}

void Input_resetKey() {
	key = '\0';
}

char Input_popKey() {
    char tempKey = key; 
    key = '\0'; 
    return tempKey;
}

char Input_getKey() {
	return key;
}