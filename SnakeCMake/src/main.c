#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "state.h"
#include "screen.h"
#include "globals.h"
#include "input.h"
#include <windows.h>
#include <time.h>


void enableANSI(void) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char* argv[]) {
	srand(time(NULL));
	enableANSI();

	State* pState = State_create();

	State_initSnake(pState); 
	State_initApples(pState);
	State_initWalls(pState);
	State_initScore(pState);
	State_createRandomWalls(pState);

	while (pState->gameOn) {
		printf("\033[2J\033[H"); // clear screen + move cursor to top-left
		char key = Input_popKey();
		
		
		if (key == KEY_LEFT) {
			State_steerSnake(pState, STEER_LEFT); // STEER_LEFT is an enum in state.h
		}
		else if (key == KEY_RIGHT) {
			State_steerSnake(pState, STEER_RIGHT);// STEER_RIGHT is an enum in state.h
		}

		Screen_setState(pState);
		Screen_print();
		State_update(pState);
		Sleep(200);
		Input_readKey();
		
		
	}
	printf("SCORE: %d \n", pState->score);
	Screen_setState(pState);
	Screen_print();

	printf("Press any key to exit...\n");
	_getch();

	return 0;
}
