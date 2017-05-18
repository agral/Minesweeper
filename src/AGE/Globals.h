#ifndef AGE_GLOBALS_H
#define AGE_GLOBALS_H

#include "Sprite.h"

#include <SDL.h>

namespace AGE
{

/**
 * The title of the game window.
 */
const char windowTitle[] = "Minesweeper";

/**
 * Holds current screen width in pixels unit.
 */
extern int screenWidth;

/**
 * Holds current screen height in pixels unit.
 */
extern int screenHeight;

/**
 * Holds the Frames Per Seconds count.
 */
const int FPS = 60;

/**
 * Holds the length of a frame in milliseconds.
 */
const int TICKS_PER_FRAME = 1000 / FPS;

/**
 * The default width of the minefield, in Fields.
 */
extern const int startingBoardWidth;

/**
 * The default height of the minefield, in Fields.
 */
extern const int startingBoardHeight;

/**
 * The default total mines count on the minefield.
 */
extern const int startingTotalMines;


/**
 * The window that everything will be rendered on.
 */
extern SDL_Window *window;

/**
 * The window renderer.
 */
extern SDL_Renderer *renderer;

/**
 * The surface contained by the window.
 */
extern SDL_Surface *screenSurface;

/**
 * The spritesheet containing minesweeper tiles:
 */
extern Sprite boardSprite;

/**
 * The spritesheet containing board borders:
 */
extern Sprite borderSprite;


extern const int TILE_SIZE;

extern SDL_Rect clipNeighbors[];

extern SDL_Rect clipFieldUnknown;
extern SDL_Rect clipRedFlag;
extern SDL_Rect clipQuestionMark;
extern SDL_Rect clipBombNormal;
extern SDL_Rect clipBombExploded;

extern SDL_Rect clipBorderNE;
extern SDL_Rect clipBorderN;
extern SDL_Rect clipBorderNW;
extern SDL_Rect clipBorderE;
extern SDL_Rect clipBorderW;
extern SDL_Rect clipBorderSE;
extern SDL_Rect clipBorderS;
extern SDL_Rect clipBorderSW;

} // namespace AGE

#endif // AGE_GLOBALS_H
