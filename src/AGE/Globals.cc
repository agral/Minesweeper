#include "Globals.h"

namespace AGE
{

int screenWidth = 800;
int screenHeight = 600;
SDL_Window *window = nullptr;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *msTilesSurface = nullptr;

const int TILE_SIZE = 13; //px;

extern const SDL_Rect clipNeighbors[9] = {
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


} // namespace AGE
