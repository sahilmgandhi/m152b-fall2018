#include "game_controller.h"

/**
 * Iniitalizes the entire game
 * 
 * @param game    struct game     The game object
 * @param level   uint8_t         The starting level
 */
void initGame(struct game *g, uint8_t level)
{
    g->initialized = 1;
    g->level = level;
    g->gameOver = 0;
    g->xLeftOld = -1;
    g->yTopOld = -1;
    g->xLeft = 24;
    g->yTop = GAME_Y - 2;
    g->propagationCount = 0;
    g->score = 0;
    g->bananaCollisions = 0;

    fillScreen(g, ROAD);

    //  g->screen[g->playerXPos][g->playerYPos] = CAR_COLOR;

    placeCarOnScreen(g);
    g->screen[25][10] = RED;
}

void placeCarOnScreen(struct game *g)
{
    g->screen[g->xLeft][g->yTop + 1] = CAR_COLOR;
    g->screen[g->xLeft + 1][g->yTop + 1] = CAR_COLOR;
    g->screen[g->xLeft + 2][g->yTop + 1] = CAR_COLOR;
    g->screen[g->xLeft + 1][g->yTop] = CAR_COLOR;
}

int detectCollision(struct game *g)
{
    if (g->screen[g->xLeft][g->yTop + 1] != ROAD && g->screen[g->xLeft][g->yTop + 1] != CAR_COLOR && g->screen[g->xLeft][g->yTop + 1] != LANE)
    {
    	if (g->screen[g->xLeft][g->yTop + 1] == YELLOW){
    		g->bananaCollisions++;
    		return 0;
    	}
        return 1;
    }
    if (g->screen[g->xLeft + 1][g->yTop + 1] != ROAD && g->screen[g->xLeft + 1][g->yTop + 1] != CAR_COLOR  && g->screen[g->xLeft + 1][g->yTop + 1] != LANE)
    {
    	if (g->screen[g->xLeft + 1][g->yTop + 1]  == YELLOW){
			g->bananaCollisions++;
			return 0;
		}
        return 2;
    }
    if (g->screen[g->xLeft + 2][g->yTop + 1] != ROAD && g->screen[g->xLeft + 2][g->yTop + 1] != CAR_COLOR && g->screen[g->xLeft + 2][g->yTop + 1] != LANE)
    {
    	if (g->screen[g->xLeft + 2][g->yTop + 1] == YELLOW){
			g->bananaCollisions++;
			return 0;
		}
        return 3;
    }
    if (g->screen[g->xLeft + 1][g->yTop] != ROAD && g->screen[g->xLeft + 1][g->yTop] != CAR_COLOR && g->screen[g->xLeft + 1][g->yTop] != LANE)
    {
    	if (g->screen[g->xLeft + 1][g->yTop] == YELLOW){
			g->bananaCollisions++;
			return 0;
		}
        return 4;
    }

    return 0;
}

/**
 * Shift the entire game down INCLUDING the bottom most row
 * It's weird to think that X is actually referring to columns and y to rows
 * 
 * @param game   struct game    The game object
 * 
 * @return int    0 if the player is dead, 1 else
 */
int propagateGame(struct game *g)
{
    int i;
    int j;
    for (i = GAME_X - 1; i > 0; i--)
    {
        for (j = 0; j < GAME_Y; j++)
        {
            g->screen[j][i] = g->screen[j][i - 1];
        }
    }

    for (j = 0; j < GAME_X; j++)
    {
        g->screen[j][0] = ROAD;
    }
    // Lane dividers:
	g->screen[10][0] = LANE;
	g->screen[20][0] = LANE;
	g->screen[30][0] = LANE;
	g->screen[40][0] = LANE;
    g->propagationCount++;
    g->score++;
    if (g ->propagationCount == 11){
    	generateObject(g);
    	g->propagationCount = 0;
    }

    int collision = detectCollision(g);
    if (collision || (!collision && g->bananaCollisions >= 3)){
    	playerDead(g);
    	return 0;
    }

    return 1;
}

/**
 * Generates the shell against the player
 *
 * @param game		struct game		The game object
 * @param color		int				The color of the shell
 * @param width		int				The size of the shell
 * @param offset 	int				The offset from the left
 */
void createShell(struct game *g, int color, int width, int offset){

	int i, j, height;
	height = width;
	if (color == BLUE){
		width = BLUE_WIDTH;
	}

	for (i = 0; i < height-2; i++){
		for (j = 0 + offset; j < width + offset; j++)
		{
			if ((j + i) % 4 == 0)
				g->screen[j][i] = SHELLWHITE;
			else
				g->screen[j][i] = color;
		}
	}
	for (i = height-2; i < height; i++){
		for (j = 0 + offset; j < width + offset; j++)
		{
			g->screen[j][i] = SHELL;
		}
	}
}

/**
 * Generates the shell against the player
 *
 * @param game		struct game		The game object
 * @param offset 	int				The offset from the left
 */
void createBanana(struct game *g, int offset)
{
    g->screen[offset][3 + 1] = YELLOW;
    g->screen[offset + 1][3 + 1] = YELLOW;
    g->screen[offset + 2][3 + 1] = YELLOW;
    g->screen[offset + 1][3] = YELLOW;
}


/**
 * Generates the enemy objects for the player
 *
 * @param game	struct game		The game object
 */
void generateObject(struct game *g){

	int r = rand() % 40;
	int offset;
	if (r >= 0 && r < 9){
		// 3 green shells
		offset = rand() % 10;
		createShell(g, GREEN, GREEN_HEIGHT, offset);
		offset = rand() % 20 + 10;
		createShell(g, GREEN, GREEN_HEIGHT, offset);
		offset = rand() % 20 + 22;
		createShell(g, GREEN, GREEN_HEIGHT, offset);
		g->score = g->score + 15;
	}
	else if (r > 8 && r < 15){
		// 2 red shells
		offset = rand() % 20;
		createShell(g, RED, RED_HEIGHT, offset);
		offset = rand() % 23 + 20;
		createShell(g, RED, RED_HEIGHT, offset);
		g->score = g->score + 25;
	}
	else if (r > 15 && r < 30){
		// Bananas
		offset = rand() % 20;
		createBanana(g, offset);
		offset = rand() % 20 + 20;
		createBanana(g, offset);
		g->score = g->score + 10;
	}
	else if (r > 29 && r < 38){
		// Empty Space (give player time to move around)
	}
	else{
		offset = rand() % 20;
		createShell(g, BLUE, BLUE_HEIGHT, offset);
		g->score = g->score + 50;
		// 1 BLUE SHELL
	}
}

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(struct game *g)
{
    g->gameOver = 1;
    fillScreen(g, GREEN);
}

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(struct game *g)
{
    g->gameOver = 1;
    fillScreen(g, RED);
}

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(struct game *g, uint32_t color)
{
    int i;
    int j;
    for (i = 0; i < GAME_X; i++)
    {
        for (j = 0; j < GAME_Y; j++)
        {
            // Basically filling out column at a time
            g->screen[i][j] = color;
        }
    }
}

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position (range from [0-47])
 * @param newY    int16_t   New Y position 
 */
void movePlayer(struct game *g, int16_t newX, int16_t newY)
{
    propagateGame(g);

    if (newX >= 0 && newX < GAME_X - 2)
    {
        g->xLeftOld = g->xLeft;
        g->xLeft = newX;
    }

    // If newY < 0, dont move it
    if (newY > 0 && newY < GAME_Y - 1)
    {
        g->yTopOld = g->yTop;
        g->yTop = newY;
    }
    placeCarOnScreen(g);
}

