#include "state.h"
#include <stdlib.h>
#include "globals.h"

//Node_deleteChain: free the memory of given linked list
static void Node_deleteChain(Node* pHead) {
	Node* pCurrent = pHead->pNode;
	Node* pDelete = pHead;
	for (;pCurrent != NULL; pCurrent = pCurrent->pNode) {
		free(pDelete);
		pDelete = pCurrent;
	}
}

static void Point_move(Point* pPoint, Direction dir) {
	switch (dir) {
	case DIRECTION_LEFT:
		pPoint->x--;
		break;
	case DIRECTION_UP:
		pPoint->y++;
		break;
	case DIRECTION_RIGHT:
		pPoint->x++;
		break;
	case DIRECTION_DOWN:
		pPoint->y--;
		break;
	default:
		break;
	}

	return;
};

static void Node_move(Node* pNode, Direction dir) {
	switch (dir) {
	case DIRECTION_LEFT:
		pNode->x--;
		break;
	case DIRECTION_UP:
		pNode->y++;
		break;
	case DIRECTION_RIGHT:
		pNode->x++;
		break;
	case DIRECTION_DOWN:
		pNode->y--;
		break;
	default:
		break;
	}
	return;
};


State* State_create() {
	return (State*)malloc(sizeof(State));
};
void State_destroy(State* pState) {
	free(pState);
	pState = NULL;
};

int State_initSnake(State* pState) {
	int middleX = SCREEN_WIDTH / 2;
	int middleY = SCREEN_WIDTH / 2;// SCREEN_WIDTH is declared in globals.h

	Node* snake = malloc(sizeof(Node));
	if (snake == NULL) {
		return 1;// failed to create snake head
	}
	pState->snake = snake;

	snake->x = middleX;
	snake->y = middleY;
	snake->pNode = NULL;

	pState->snakeDirection = DIRECTION_LEFT;

	if (State_extendSnake(pState)) { // Initially the snake should have a length of 2
		return 2; // failed to extend the snake
	};
	return 0;
}

int State_extendSnake(State* pState) {
	Node* newHead = malloc(sizeof(Node));
	if (newHead == NULL) {
		return 1; // failed to create snake head
	}

	newHead->x = pState->snake->x;
	newHead->y = pState->snake->y;

	newHead->pNode = pState->snake;

	Node_move(pState->snake, pState->snakeDirection);

	return 0;
}

int State_moveSnake(State* pState) {
	Node* current = pState->snake;

	// move the body 1 block forward
	for (;current->pNode != NULL;current = current->pNode) {
		current->pNode->x = current->x;
		current->pNode->y = current->y;
	}

	//move the head in snake direction
	Node_move(pState->snake, pState->snakeDirection);

	return 0;
}

int State_steerSnake(State* pState, Steer steer) {
	pState->snakeDirection = (pState->snakeDirection + steer) % DIRECTION_SIZE;
	return 0;
}

void State_deleteSnake(State* pState) {
	Node_deleteChain(pState->snake);
}


int State_initApples(State* pState) {
	pState->nApples = 0;
	return 0;
}


int State_createRandomApple(State* pState) {
	int randX = rand() % SCREEN_WIDTH;
	int randY = rand() % SCREEN_HEIGHT;//SREEN_HEIGHT is defined in globals.h

	Point* apple = malloc(sizeof(Point));
	if (apple == NULL) {
		return 1;
	}

	apple->x = randX;
	apple->y = randY;

	pState->apple[pState->nApples] = apple;

	return 0;
}

int State_destroyApple(State* pState, int x, int y) {
	Point** appleArr = pState->apple;
	for (int i = 0; i < pState->nApples; i++) {
		if ((appleArr[i]->x) == x && (appleArr[i]->y == y)) {
			free(&appleArr[i]);
			//fill the space created by remove operation
			appleArr[i] = appleArr[pState->nApples - 1];
			pState->nApples--;

			return 0;
		}
	}
	return 1;
}


int State_initWalls(State* pState) {
	pState->nWalls = 0;
	return 0;
}


int State_createRandomWalls(State* pState) {
	int nWalls = rand() % MAX_WALLS;
	int DIRECTION_OPPOSITE = DIRECTION_SIZE / 2;
	int PROHIBITED_DIR = DIRECTION_SIZE;//PROHIBITED_DIR is needed to be initialized; initialize it with a variable outside of direction scope meaning any direction can be used as the first step

	for (int i = 0; i < nWalls; i++) {
		//create first random point
		int startX = rand() % (SCREEN_WIDTH - WALL_DISTANCE) + WALL_DISTANCE;
		int startY = rand() % (SCREEN_HEIGHT - WALL_DISTANCE) + WALL_DISTANCE;
		int wallLength = rand() % MAX_WALL_LENGTH;

		//create linked list head to hold wall
		Node* pWall = malloc(sizeof(Node));
		if (pWall == NULL) {
			return 1;
		}
		pWall->x = startX;
		pWall->y = startY;

		Node* pCurrent = pWall;

		for (int j = 0; j < wallLength; j++) {
			Node* pNext = malloc(sizeof(Node));
			pNext->x = pCurrent->x;
			pNext->y = pCurrent->y;

			pCurrent->pNode = pNext;
			pCurrent = pNext;

			int direction;
			while ((direction = rand() % DIRECTION_SIZE) == PROHIBITED_DIR);
			PROHIBITED_DIR = (direction + DIRECTION_OPPOSITE) % DIRECTION_SIZE;// DIRECTION_SIZE is defined in header

			Node_move(pCurrent, direction);
		}
		pCurrent->pNode = NULL;
	}
	return 0;
};




















