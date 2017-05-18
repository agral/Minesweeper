#include "Engine.h"

#include "Globals.h"
#include "Timer.h"
#include "../Field.h" // for FlagCode
#include "../Log/Logger.h"

#include <SDL.h>
#include <SDL_image.h>

namespace AGE
{

Engine::Engine() :
  _isInitialized(false),
  _isClosed(false),
  _board(startingBoardHeight, startingBoardWidth)
{
  _board.newGame(startingTotalMines);

  _boardHeightPx = _board.height() * TILE_SIZE;
  _boardWidthPx = _board.width() * TILE_SIZE;
  _boardOffsetY = (screenHeight - _boardHeightPx) / 2;
  _boardOffsetX = (screenWidth - _boardWidthPx) / 2;
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
    Log::DEBUG() << "Initializing the SDL";
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      Log::ERROR() << "SDL failed to initialize!";
      Log::ERROR() << "SDL error: " << SDL_GetError();
      successFlag = false;
    }
    else
    {
      // Sets linear texture filtering:
      Log::DEBUG() << "Setting linear texture filtering";
      if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
      {
        Log::WARNING() << "Could not enable linear texture filtering.";
      }

      Log::VERBOSE() << "Creating the game window";
      window = SDL_CreateWindow(
          windowTitle,
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          screenWidth, screenHeight, SDL_WINDOW_SHOWN
          );
      if (nullptr == window)
      {
        Log::ERROR() << "SDL window could not be created!";
        Log::ERROR() << "SDL error: " << SDL_GetError();
        successFlag = false;
      }
      else
      {
        Log::VERBOSE() << "Creating a vertical-synced renderer";
        renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (nullptr == renderer)
        {
          Log::ERROR() << "Could not create a vsynced renderer!";
          Log::ERROR() << "SDL error: " << SDL_GetError();
          successFlag = false;
        }
        else
        {
          Log::VERBOSE() << "Initializing the IMG module";
          int imgFlags = IMG_INIT_PNG;
          if (!(IMG_Init(imgFlags) & imgFlags))
          {
            Log::ERROR() << "SDL_Image module could not initialize.";
            Log::ERROR() << "SDL_image error: ", IMG_GetError();
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

  Log::VERBOSE() << "Loading the Board sprite";
  boardSprite.loadFromFile("./Graphics/Tiles.png", renderer);

  Log::VERBOSE() << "Loading the Border sprite";
  borderSprite.loadFromFile("./Graphics/Border.png", renderer);

  return successFlag;
}


void Engine::startLoop()
{
  SDL_Event sdlEvent;
  bool quitFlag = false;

  Timer fpsTimer;
  Timer fpsCapTimer;
  int countedFrames = 0;
  fpsTimer.start();

  while (!quitFlag)
  {
    fpsCapTimer.start();

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

        int tileX = (x - _boardOffsetX) / TILE_SIZE;
        int tileY = (y - _boardOffsetY) / TILE_SIZE;

        // Left mouse button:
        if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
          Log::DEBUG() << "[Mouse] LMB (" << x << ", " << y << ") "
              << "[tile: (" << tileX << ", " << tileY << "])";
          _board.discover(tileY, tileX);
        }

        // Right mouse button:
        else if (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
          Log::DEBUG() << "[Mouse] RMB (" << x << ", " << y << ") "
              << "[tile: (" << tileX << ", " << tileY << "])";
          _board.cycleFlag(tileY, tileX);
        }

        // Middle mouse button:
        else if (buttonState & SDL_BUTTON(SDL_BUTTON_MIDDLE))
        {
          Log::DEBUG() << "[Mouse] MMB (" << x << ", " << y << ") "
              << "[tile: (" << tileX << ", " << tileY << "])";
          _board.newGame(_board.totalMines());
        }
      }

      // --- Game logic (handled in input section) ---
      double avgFps = countedFrames / (fpsTimer.ticks() / 1000.0);
      if (avgFps > 2000000)
      {
        avgFps = 0;
      }

      // --- Redraws the board: ---
      draw();

      countedFrames += 1;
      int frameTicks = fpsCapTimer.ticks();
      if(frameTicks < TICKS_PER_FRAME)
      {
        SDL_Delay(TICKS_PER_FRAME - frameTicks);
      }
    }
  }
}


void Engine::close()
{
  if (!_isClosed)
  {
    boardSprite.free();
    borderSprite.free();

    Log::DEBUG() << "[SDL] Destroying the renderer";
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    Log::DEBUG() << "[SDL] Destroying the game window";
    SDL_DestroyWindow(window);
    window = nullptr;

    Log::DEBUG() << "[SDL] Quitting the SDL";
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
  int oX = _boardOffsetX;
  int oY = _boardOffsetY;

  // Draws only known fields (while the game is still in progress)
  if ((_board.state() == GameState::FRESH) ||
      (_board.state() == GameState::IN_PROGRESS))
  {
    for (int y = 0; y < _board.height(); ++y)
    {
      int posY = (TILE_SIZE * y) + oY;
      for (int x = 0; x < _board.width(); ++x)
      {
        int posX = (TILE_SIZE * x) + oX;
        Field f = _board.peekAt(y, x);

        if (f.isKnown())
        {
          if (f.isBomb())
          {
            boardSprite.render(posX, posY, &clipBombNormal);
          }
          else
          {
            int n = f.adjacentBombsCount();
            boardSprite.render(posX, posY, &clipNeighbors[n]);
          }
        }
        else
        {
          if (FlagCode::Mine == f.flagCode())
          {
            boardSprite.render(posX, posY, &clipRedFlag);
          }
          else if (FlagCode::Unknown == f.flagCode())
          {
            boardSprite.render(posX, posY, &clipQuestionMark);
          }
          else
          {
            boardSprite.render(posX, posY, &clipFieldUnknown);
          }
        }
      }
    }
  }

  else if ((_board.state() == GameState::LOST) ||
           (_board.state() == GameState::WON))
  {
    for (int y = 0; y < _board.height(); ++y)
    {
      int posY = (TILE_SIZE * y) + oY;
      for (int x = 0; x < _board.width(); ++x)
      {
        int posX = (TILE_SIZE * x) + oX;
        Field f = _board.peekAt(y, x);

        if (f.isBomb())
        {
          boardSprite.render(posX, posY, &clipBombNormal);
        }
        else // f has to be a normal field
        {
          int n = f.adjacentBombsCount();
          boardSprite.render(posX, posY, &clipNeighbors[n]);
        }
      }
    }
  }

  // Draws the border:
  borderSprite.render(oX - TILE_SIZE    , oY - TILE_SIZE     , &clipBorderNE);
  borderSprite.render(oX + _boardWidthPx, oY - TILE_SIZE     , &clipBorderNW);
  borderSprite.render(oX - TILE_SIZE    , oY + _boardHeightPx, &clipBorderSE);
  borderSprite.render(oX + _boardWidthPx, oY + _boardHeightPx, &clipBorderSW);
  for (int x = 0; x < _board.width(); ++x)
  {
    borderSprite.render(x * TILE_SIZE + oX, oY - TILE_SIZE     , &clipBorderN);
    borderSprite.render(x * TILE_SIZE + oX, oY + _boardHeightPx, &clipBorderS);
  }
  for (int y = 0; y < _board.height(); ++y)
  {
    borderSprite.render(oX - TILE_SIZE    , y * TILE_SIZE + oY, &clipBorderE);
    borderSprite.render(oX + _boardWidthPx, y * TILE_SIZE + oY, &clipBorderW);
  }

  // Finally renders everything on-screen:
  SDL_RenderPresent(renderer);
}

} // namespace AGE
