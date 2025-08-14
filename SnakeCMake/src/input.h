#ifndef INPUT_H
#define INPUT_H

void Input_readKey();// updates the key variable according to keyboard press
char Input_getKey();// returns the key variable
void Input_resetKey();
char Input_popKey(); // returns the key and resets the variable that holds the key

#endif 
