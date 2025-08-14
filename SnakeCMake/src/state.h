#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

#define MAX_APPLES 10
#define MAX_WALLS 10
#define MAX_WALL_LENGTH 20
#define WALL_DISTANCE 10 // distance of wall to the edge of screen

typedef enum {
	DIRECTION_LEFT = 0,
	DIRECTION_UP = 1,
	DIRECTION_RIGHT = 2,
	DIRECTION_DOWN = 3,
	DIRECTION_SIZE = 4, // Used to modulo numbers to fit within the Direction range like: (Direction.DOWN + Steer.RIGHT) % Direction.SIZE = 0 which is left
} Direction;

typedef enum {
	STEER_LEFT = -1,
	STEER_RIGHT = 1,
} Steer;

typedef enum {
	GAME_OVER = 0,
} GameState;

typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Node {
	int x;
	int y;
	struct Node* pNode;
} Node;

typedef struct State {
	Node* snake;
	Point* apple[MAX_APPLES];
	Node* wall[MAX_WALLS];
	Direction snakeDirection;
	int nApples;
	int nWalls;
	int score;
	bool gameOn;
} State;

State* State_create();
void State_destroy(State*);
void State_update(State*);//moves the snake in direction; maybe cretes a random apple; checks if the game is over

int State_initSnake(State*);
void State_deleteSnake(State*);
int State_moveSnake(State*);
int State_extendSnake(State*);
int State_steerSnake(State*, Steer); // Changes the snake's direction


int State_initApples(State* pState);
int State_createRandomApple(State*); // Adds an apple with random position to apples list
int State_destroyApple(State*, int x, int y); // destroys the apple at given point 

int State_initWalls(State*);
int State_createRandomWalls(State*);
int State_destroyWalls(State*); // destroy all the walls (it is unnecessary to destroy a specific wall. When the game ends all walls will get destroyed)

void State_initScore(State*);

#endif
