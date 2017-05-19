#include "Globals.h"

namespace AGE
{

int screenWidth = 800;
int screenHeight = 600;

const int startingBoardWidth = 10;
const int startingBoardHeight = 10;
const int startingTotalMines = 5;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *screenSurface = nullptr;

Sprite boardSprite;
Sprite borderSprite;

const int TILE_SIZE = 14; //px;

SDL_Rect clipNeighbors[9] = {
  {0, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {2 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {3 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {4 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {6 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {7 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE},
  {8 * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE}
};

SDL_Rect clipFieldUnknown = {0, 0, TILE_SIZE, TILE_SIZE};
SDL_Rect clipRedFlag = {TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
SDL_Rect clipQuestionMark = {2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
SDL_Rect clipBombNormal = {3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
SDL_Rect clipBombExploded = {4 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};

SDL_Rect clipBorderNE = {0            , 0            , TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderN  = {TILE_SIZE    , 0            , TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderNW = {2 * TILE_SIZE, 0            , TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderE  = {0            , TILE_SIZE    , TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderW  = {2 * TILE_SIZE, TILE_SIZE    , TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderSE = {0            , 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderS  = {TILE_SIZE    , 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
SDL_Rect clipBorderSW = {2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE};

} // namespace AGE
