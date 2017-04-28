#include "Engine.h"

#include "Globals.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

namespace AGE
{

Engine::Engine() :
  _isInitialized(false),
  _isClosed(false),
  _board(startingBoardHeight, startingBoardWidth)
{
  _board.newGame(startingTotalMines);
}


Engine::~Engine()
{
  close();
}


bool Engine::init()
{
  bool successFlag = true;
  if (!_isInitialized)
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("SDL failed to initialize.\nSDL error: %s\n", SDL_GetError());
      successFlag = false;
    }
    else
    {
      // Sets linear texture filtering:
      if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
      {
        printf("Warning: Could not enable linear texture filtering.\n");
      }

      window = SDL_CreateWindow(
          windowTitle,
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          screenWidth, screenHeight, SDL_WINDOW_SHOWN
          );
      if (nullptr == window)
      {
        printf("SDL window could not be created!\nSDL error: %s\n",
            SDL_GetError());
        successFlag = false;
      }
      else
      {
        renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (nullptr == renderer)
        {
          printf("Could not create a vsynced renderer.\n");
          printf("SDL error: %s\n", SDL_GetError());
          successFlag = false;
        }
        else
        {
          int imgFlags = IMG_INIT_PNG;
          if (!(IMG_Init(imgFlags) & imgFlags))
          {
            printf("SDL_Image module could not initialize.\n");
            printf("SDL_image error: %s\n", IMG_GetError());
            successFlag = false;
          }
          else
          {
            screenSurface = SDL_GetWindowSurface(window);
          }
        }
      }
    }

    _isInitialized = true;
  }
  return successFlag;
}


bool Engine::loadMedia()
{
  bool successFlag = true;

  boardSprite.loadFromFile("./Graphics/Tiles.png", renderer);

  return successFlag;
}


void Engine::startLoop()
{
  SDL_Event sdlEvent;
  bool quitFlag = false;
  while (!quitFlag)
  {
    while (0 != SDL_PollEvent(&sdlEvent))
    {
      // --- Processes user's input: ---

      // Case: user quits the application:
      if (SDL_QUIT == sdlEvent.type)
      {
        quitFlag = true;
      }

      // Case: user clicks with a mouse:
      else if (SDL_MOUSEBUTTONDOWN == sdlEvent.type)
      {
        int x, y;
        Uint32 buttonState = SDL_GetMouseState(&x, &y);

        int tileX = x / TILE_SIZE;
        int tileY = y / TILE_SIZE;
        printf("Tile: (y=%d, x=%d)\n", tileY, tileX);

        // Left mouse button:
        if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
          printf("[Mouse] Left button pressed.\n");
          _board.discover(tileY, tileX);
        }

        // Right mouse button:
        else if (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
          printf("[Mouse] Right button pressed.\n");
          _board.print();
        }

        // Middle mouse button:
        else if (buttonState & SDL_BUTTON(SDL_BUTTON_MIDDLE))
        {
          printf("[Mouse] Middle button pressed.\n");
          _board.newGame(_board.totalMines());
        }
      }

      // --- Redraws the board: ---
      draw();
    }
  }
}


void Engine::close()
{
  if (!_isClosed)
  {
    boardSprite.free();

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();

    _isClosed = true;
  }
}

// private methods:

void Engine::draw()
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  for (int y = 0; y < _board.height(); ++y)
  {
    for (int x = 0; x < _board.width(); ++x)
    {
      Field f = _board.peekAt(y, x);
      if (f.isBomb())
      {
        boardSprite.render(TILE_SIZE * x, TILE_SIZE * y, &clipBombNormal);
      }
      else
      {
        int n = f.adjacentBombsCount();
        boardSprite.render(TILE_SIZE * x, TILE_SIZE * y, &clipNeighbors[n]);
      }
    }
  }

  SDL_RenderPresent(renderer);
}

} // namespace AGE
