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

/*Screen_setState: */
static char screen[SCREEN_SIZE + 1];// +1 for '\0'

void Screen_reset() {
	//reset the screen
	int i;
	for (i = 0; i <= SCREEN_SIZE; i++) {
		screen[i] = ' ';
	}

}

//Screen_setPoint: set a character at screen for given position of (x, y)
void Screen_setPoint(int x, int y, char c) {
	int i = y * SCREEN_WIDTH + x;
	screen[i] = c;
}

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
	Screen_setPoint(cSnake->x, cSnake->y, SNAKE_HEAD_CHARACTER);
	while ((cSnake = cSnake->pNode) != NULL) {
		Screen_setPoint(cSnake->x, cSnake->y, SNAKE_BODY_CHARACTER);
	}

}
//printScreen:
void Screen_print() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			printf("%c", screen[j]);
		}
		printf("\n");
	}
}