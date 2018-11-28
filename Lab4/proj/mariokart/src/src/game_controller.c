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
    g->playerXPos = 0;
    g->playerYPos = 0;
    g->playerXLastPos = -1;
    g->playerYLastPos = -1;

    fillScreen(g, ROAD);

    g->screen[g->playerXPos][g->playerYPos] = CAR_COLOR;
}

/**
 * Shift the entire game down INCLUDING the bottom most row
 * 
 * @param game   struct game    The game object
 * 
 * @return int    0 if the player is dead, 1 else
 */
int propagateGame(struct game *game)
{
    int i;
    int j;
    for (i = GAME_X - 1; i > 0; i--)
    {
        for (j = 0; j < GAME_Y; j++)
        {
            game->screen[i][j] = game->screen[i - 1][j];
        }
    }

    // At this point, we need add the top most row to be filled with EITHER:
    // spaces, or some kind of blocks????????
    // black for now
    // TODO: Generate some random top most row here:
    for (j = 0; j < GAME_Y; j++)
    {
        game->screen[0][j] = ROAD;
    }

    // TODO: In this function, after moving everything down, you should check if the player has died

    if (game->screen[game->playerXPos][game->playerYPos] != ROAD)
    {
        playerDead(game);
        return 0;
    }

    return 1;
}

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(struct game *game)
{
    game->gameOver = 1;
    fillScreen(game, GREEN);
}

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(struct game *game)
{
    game->gameOver = 1;
    fillScreen(game, RED);
}

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(struct game *game, uint32_t color)
{
    int i;
    int j;
    for (i = 0; i < GAME_X; i++)
    {
        for (j = 0; j < GAME_Y; j++)
        {
            // Basically filling out column at a time
            game->screen[i][j] = color;
        }
    }
}

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position 
 * @param newY    int16_t   New Y position 
 */
void movePlayer(struct game *game, int16_t newX, int16_t newY)
{
    game->playerXLastPos = game->playerXPos;
    game->playerYLastPos = game->playerYPos;

    game->playerXPos = newX;
    game->playerYPos = newY;

    game->screen[game->playerXPos][game->playerYPos] = CAR_COLOR;
}

// void textOnTopLeft(struct game *game, char[] text)
// {
//   Bitmap *b = bm_create(128, 128);

//   bm_set_color(b, bm_atoi("white"));
//   bm_puts(b, 30, 60, text);

//   for (int i = 0; i < 128; i++)
//   {
//     for (int j = 0; j < 128; j++)
//     {
//       game->screen[i][j] = bm_get(b, i, j);
//       //printf("%d", bm_get(b, 60, 60));
//     }
//   }

//   bm_free(b);
// }
