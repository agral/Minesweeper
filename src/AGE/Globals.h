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
 * The surface containing minesweeper tiles:
 */
extern Sprite boardSprite;


extern const int TILE_SIZE;

extern SDL_Rect clipNeighbors[];

extern SDL_Rect clipFieldUnknown;
extern SDL_Rect clipRedFlag;
extern SDL_Rect clipQuestionMark;
extern SDL_Rect clipBombNormal;
extern SDL_Rect clipBombExploded;

} // namespace AGE

#endif // AGE_GLOBALS_H
