#define MAX_NUMBER_OF_OBSTACLES 5
#define CAR_Y_OFFSET 5
#define OBSTACLE_SIZE 5
#define X_MAX 2560
#define Y_MAX 720
#include <stdio.h>
srand(time(0));

#define SPACE 0
#define OBSTACLE 1
#define CAR 2
int screen[X_MAX][Y_MAX];

void init(){
	//Fill emptiness
	for(int i = 0; i < X_MAX; i++){
		for(int j = 0; j < Y_MAX; j++){
			screen[i][j] = SPACE;
		}
	}
	//Fill car at the bottom of screen
	for(int i = X_MAX / 2 - 2; i < Y_MAX / 2 + 2; i++){
		for(int j = Y_MAX - CAR_Y_OFFSET; j < Y_MAX - CAR_Y_OFFSET - 4; j++){
			screen[i][j] = CAR;
		}
	}
}

void shiftScreenDown(){
	//Shift everything down
	for (int i = X_MAX-2; i >= 0; i--){
		screen[i+1] = screen[i]; //TODO: does this work
	}
	//Fill top row with space
	for (int j = 0; j < Y_MAX; j++){
		screen[0][j] = SPACE;		
	}	
}

void addObstacle(){
	yPosition = rand() % Y_MAX - 1 - OBSTACLE_SIZE ; //this y value is the left edge
	for (int j = yPosition; j < yPosition + OBSTACLE_SIZE; j++){
		for (int i = 0; i < OBSTACLE_SIZE; i++){
			screen[i][j] = OBSTACLE;
		}
	}
}

int main()
{
	init();
    return 0;
}