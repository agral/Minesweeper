#include "Engine.h"

#include "Globals.h"
#include "SdlFunctions.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

namespace AGE
{

Engine::Engine() :
  _isInitialized(false),
  _isClosed(false)
{
  // All the work is done in the initialization block.
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
      // extern SDL_Window *window;
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

    _isInitialized = true;
  }
  return successFlag;
}


bool Engine::loadMedia()
{
  bool successFlag = true;

  msTilesSurface = loadSurface("./Graphics/Tiles.png", true);

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

        // Left mouse button:
        if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
          printf("LMB(%03d, %03d)\n", x, y);
        }

        // Right mouse button:
        else if (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
          printf("RMB(%03d, %03d)\n", x, y);
        }
      }

      SDL_BlitSurface(msTilesSurface, 0, screenSurface, 0);
      SDL_UpdateWindowSurface(window);
    }
  }
}


void Engine::close()
{
  if (!_isClosed)
  {
    SDL_FreeSurface(msTilesSurface);
    msTilesSurface = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();

    _isClosed = true;
  }
}

} // namespace AGE
