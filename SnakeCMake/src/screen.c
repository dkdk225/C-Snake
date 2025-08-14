#include "state.h"
#include "screen.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_SIZE SCREEN_HEIGHT * SCREEN_WIDTH

#define WALL_CHARACTER '#'
#define SNAKE_BODY_CHARACTER '+'
#define SNAKE_HEAD_CHARACTER '@'
#define APPLE_CHARACTER 'O'
#define RESET_CHARACTER ' '

/*Screen_setState: */
static char screen[SCREEN_SIZE + 1];// +1 for '\0'

void Screen_reset() {
	//reset the screen
	int i;
	for (i = 0; i <= SCREEN_SIZE; i++) {
		screen[i] = RESET_CHARACTER;
	}
}

//Screen_setPoint: set a character at screen for given position of (x, y)
void Screen_setPoint(int x, int y, char c) {
	int i = (y * SCREEN_WIDTH) + x;
	screen[i] = c;
}

/*Screen_setState: changes the stcreen string according to state*/
void Screen_setState(State* pState) {
	Screen_reset();
	//print the walls
	for (int i = 0; i < pState->nWalls; i++) {
		Node* cWall = pState->wall[i];// current wall
		Screen_setPoint(cWall->x, cWall->y, WALL_CHARACTER);
		while ((cWall = cWall->pNode) != NULL) {
			Screen_setPoint(cWall->x, cWall->y, WALL_CHARACTER);
		}
	}

	//print the apples
	for (int i = 0; i < pState->nApples; i++) {
		Point* cApple = pState->apple[i]; //current apple
		Screen_setPoint(cApple->x, cApple->y, APPLE_CHARACTER);
	}

	//print the snake
	Node* cSnake = pState->snake;
	while ((cSnake = cSnake->pNode) != NULL) {
		Screen_setPoint(cSnake->x, cSnake->y, SNAKE_BODY_CHARACTER);
	}
	Screen_setPoint(pState->snake->x, pState->snake->y, SNAKE_HEAD_CHARACTER); // head should be printed after the body so that it overwrites body pieces
}
//printScreen:
void Screen_print() {
	// print outline; top line
	for (int i = 0; i < SCREEN_WIDTH + 2; i++) {
		printf("%c", WALL_CHARACTER);
	}
	printf("\n");

	//print screen variable
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		printf("%c", WALL_CHARACTER);// OUTLINE;left line
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			printf("%c", screen[(i * SCREEN_WIDTH) + j]);
		}
		printf("%c", WALL_CHARACTER);// OUTLINE; right line
		printf("\n");
	}

	// print outline; bottom line
	for (int i = 0; i < SCREEN_WIDTH + 2; i++) {
		printf("%c", WALL_CHARACTER);
	}
	printf("\n");
}