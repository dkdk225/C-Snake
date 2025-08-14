#include "state.h"
#include <stdlib.h>
#include "globals.h"
#include <stdbool.h>

static bool State_appleExists(State*, int, int);
static bool State_wallExists(State*, int, int);
static bool State_snakeHeadInScreen(State*);
static bool State_snakeBitesItself(State*);

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
		pPoint->y--;
		break;
	case DIRECTION_RIGHT:
		pPoint->x++;
		break;
	case DIRECTION_DOWN:
		pPoint->y++;
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
		pNode->y--;
		break;
	case DIRECTION_RIGHT:
		pNode->x++;
		break;
	case DIRECTION_DOWN:
		pNode->y++;
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
	int middleY = SCREEN_HEIGHT / 2;// SCREEN_WIDTH is declared in globals.h

	Node* snake = malloc(sizeof(Node));
	if (snake == NULL) {
		return 1;// failed to create snake head
	}
	pState->snake = snake;

	snake->x = middleX;
	snake->y = middleY;
	snake->pNode = NULL;

	pState->snakeDirection = DIRECTION_LEFT;
	if (State_extendSnake(pState) != 0) { // Initially the snake should have a length of 2
		return 2; // failed to extend the snake
	};
	return 0;
}

void State_update(State* pState) {
	//check if the snake collides with an apple
		//yes ? then extend the snake in direction; remove the apple
		// no ? then move the snake in direction
	
	//check if the snake collides with the walls or outside frame
	//check if the head of the snake collides with any of the body

	//maybe create a random apple

	//loop over snake look if any of the points collide with walls or apples
	// you just need to check the snake head for collisions

	Point snakeHead = { 
		pState->snake->x,
		pState->snake->y
	};
	Point_move(&snakeHead, pState->snakeDirection);
	if (State_appleExists(pState, snakeHead.x, snakeHead.y)) {
		State_extendSnake(pState);
		State_destroyApple(pState, snakeHead.x, snakeHead.y);
		pState->score += 10;
	}
	else {
		State_moveSnake(pState);
	}

	if (State_wallExists(pState, pState->snake->x, pState->snake->y)) {
		printf("SNAKE HIT A WALL \n");
		pState->gameOn = false;
	}
	if (!State_snakeHeadInScreen(pState)) {
		printf("SNAKE IS OUTSIDE THE SCREEN\n");
		pState->gameOn = false;
	}
	if (State_snakeBitesItself(pState)) {
		printf("SNAKE BIT ITSELF \n");
		pState->gameOn = false;
	}
	if (pState->nApples < MAX_APPLES && (rand() % 10 == 0)) {
		State_createRandomApple(pState);
	}
}

int State_extendSnake(State* pState) {
	Node* newHead = malloc(sizeof(Node));
	if (newHead == NULL) {
		return 1; // failed to create snake head
	}

	newHead->x = pState->snake->x;
	newHead->y = pState->snake->y;

	newHead->pNode = pState->snake;
	pState->snake = newHead;

	Node_move(pState->snake, pState->snakeDirection);

	return 0;
}

int State_moveSnake(State* pState) {
	Node* current = pState->snake;
	int tempX;
	int tempY; //temporary holder to not lose the previous position values
	
	int setX = pState->snake->x;
	int setY = pState->snake->y; //holder to set the variables

	// move the body 1 block forward
	for (;current->pNode != NULL;current = current->pNode) {
		tempX = current->pNode->x;
		tempY = current->pNode->y;
		current->pNode->x = setX;
		current->pNode->y = setY;
		setX = tempX;
		setY = tempY;
	}

	//move the head in snake direction
	Node_move(pState->snake, pState->snakeDirection);

	return 0;
}

int State_steerSnake(State* pState, Steer steer) {
	Direction newDirection = pState->snakeDirection + steer;

	if (newDirection < 0) {
		newDirection += DIRECTION_SIZE;
	}
	pState->snakeDirection = (newDirection) % DIRECTION_SIZE;
	return 0;
}

void State_deleteSnake(State* pState) {
	Node_deleteChain(pState->snake);
}

static bool State_snakeHeadInScreen(State* pState) {
	//check if the snake head is in screen; check it at each state update
	//snake body follows the head; if the head doesn't leave the screen neither does the body

	Node* hSnake = pState->snake;// snake head
	if (
		((hSnake->x >= 0) && (hSnake->x < SCREEN_WIDTH))
		&&
		((hSnake->y >= 0) && (hSnake->y < SCREEN_HEIGHT))
		)
		return true;
	
	return false;
}

static bool State_snakeBitesItself(State* pState) {
	Node* hSnake = pState->snake; // snake head
	Node* cSnake = hSnake->pNode; // current snake-body point 
	for (;cSnake != NULL; cSnake = cSnake->pNode) {
		if ((cSnake->x == hSnake->x) && (cSnake->y == hSnake->y)) 
			return true;
	}
	return false;
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
	pState->nApples++;

	return 0;
}

int State_destroyApple(State* pState, int x, int y) {
	Point** appleArr = pState->apple;
	for (int i = 0; i < pState->nApples; i++) {
		if ((appleArr[i]->x) == x && (appleArr[i]->y == y)) {
			free(appleArr[i]);
			//fill the space created by remove operation
			appleArr[i] = appleArr[pState->nApples - 1];
			pState->nApples--;

			return 0;
		}
	}
	return 1;
}

static bool State_appleExists(State* pState, int x, int y) {
	Point** appleArr = pState->apple;
	for (int i = 0; i < pState->nApples; i++) {
		if ((appleArr[i]->x) == x && (appleArr[i]->y == y)) {
			return true;
		}
	}
	return false;
}

int State_initWalls(State* pState) {
	pState->nWalls = 0;
	return 0;
}


int State_createRandomWalls(State* pState) {
	int nWalls = rand() % MAX_WALLS;
	pState->nWalls = nWalls;

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
		pState->wall[i] = pWall;

		pWall->x = startX;
		pWall->y = startY;

		Node* pCurrent = pWall;

		int direction = rand() % DIRECTION_SIZE;
		for (int j = 0; j < wallLength; j++) {
			Node* pNext = malloc(sizeof(Node));
			if (pNext == NULL) {
				return 1;
			}
			pNext->x = pCurrent->x;
			pNext->y = pCurrent->y;

			pCurrent->pNode = pNext;
			pCurrent = pNext;

			//maybe change the buiding direction of the wall
			if (rand() % 5 == 0) {
				while ((direction = rand() % DIRECTION_SIZE) == PROHIBITED_DIR);
				PROHIBITED_DIR = (direction + DIRECTION_OPPOSITE) % DIRECTION_SIZE;// DIRECTION_SIZE is defined in header
			}
			
			Node_move(pCurrent, direction);
		}
		pCurrent->pNode = NULL;
	}
	return 0;
};

static bool State_wallExists(State* pState, int x, int y) {
	Node** walls = pState->wall;

	for (int i = 0; i < pState->nWalls; i++) {  // loop over all walls
		Node* cWall = pState->wall[i];
		
		for (;cWall != NULL; cWall = cWall->pNode)  // go through linked lists (walls)
			if ((cWall->x == x) && (cWall->y == y))
				return true;	
	}

	return false;
}

void State_initScore(State* pState) {
	pState->score = 0;
}

















