#include "Board.h"
#include "Log/Logger.h"
#include <random>

Board::Board(int height, int width) :
  _height(height),
  _width(width),
  _state(GameState::FRESH)
{
  Log::TRACE() << "Entering the Board class constructor...";
  _map.resize(height);
  for(int h = 0; h < height; ++h)
  {
    _map[h].resize(width);
  }
}

Field Board::peekAt(int y, int x)
{
  return _map[y][x];
}

int Board::width()
{
  return _width;
}

int Board::height()
{
  return _height;
}

int Board::totalMines()
{
  return _totalMines;
}

void Board::clear()
{
  Log::TRACE() << "Entering the Board::clear() method...";
  Log::DEBUG() << "[Board] Clearing the board.";
  for(int h = 0; h < _height; ++h)
  {
    for(int w = 0; w < _width; ++w)
    {
      _map[h][w].clear();
    }
  }

  _state = GameState::FRESH;
}

void Board::calculateAdjacentBombsCount()
{
  Log::TRACE() <<
      "Entering the Board::calculateAdjacentBombsCount() method...";
  for(int h = 0; h < _height; ++h)
  {
    for(int w = 0; w < _width; ++w)
    {
      int count = 0;
      if ((h > 0) && (w > 0) && (_map[h-1][w-1].isBomb()))
        count += 1; // top left neighbor is a bomb.

      if ((h > 0) && (_map[h-1][w].isBomb()))
        count += 1; // top neighbor is a bomb.

      if ((h > 0) && (w < _width-1) && (_map[h-1][w+1].isBomb()))
        count += 1; // top right neighbor is a bomb.

      if ((w > 0) && (_map[h][w-1].isBomb()))
        count += 1; // left neighbor is a bomb.

      if ((w < _width-1) && (_map[h][w+1].isBomb()))
        count += 1; // right neighbor is a bomb.

      if ((h < _height-1) && (w > 0) && (_map[h+1][w-1].isBomb()))
        count += 1; // bottom left neighbor is a bomb.

      if ((h < _height-1) && (_map[h+1][w].isBomb()))
        count += 1; // bottom neighbor is a bomb.

      if ((h < _height-1) && (_map[h+1][w+1].isBomb()))
        count += 1; // bottom right neighbor is a bomb.

      _map[h][w].setAdjacentBombsCount(count);
    }
  }
}

void Board::discover(int y, int x)
{
  Log::TRACE() << "Entering the Board::discover() method...";
  // Does nothing for the cells outside the minefield:
  if ((y < 0) || (y >= _height) || (x < 0) || (x >= _width))
  {
    Log::VERBOSE() << "[Board][Discover] Tile: (" << y << ", " << x <<
        ") is outside of the minefield - not discovering.";
    return;
  }

  // Does not discover fields if the game has ended.
  if (!((_state == GameState::FRESH) || (_state == GameState::IN_PROGRESS)))
  {
    Log::VERBOSE() << "[Board][Discover] The game has ended - not discovering.";
    return;
  }

  // Does nothing if a field is known (discovered) already:
  if (_map[y][x].isKnown())
  {
    Log::VERBOSE() << "[Board][Discover] Tile: (" << y << ", " << x <<
        ") is already known - not discovering.";
    return;
  }


  Log::DEBUG() <<
      "[Board][Discover] Revealing tile: (" << y << ", " << x << ").";

  if (_map[y][x].isBomb())
  {
    Log::INFO() << "[Board] GAME OVER.";
    _state = GameState::LOST;
  }
  else
  {
    _map[y][x].setIsKnown(true);
    _map[y][x].setFlagCode(FlagCode::Empty);

    // Discovers neighbors automatically if adjacentBombsCount is zero:
    if (0 == _map[y][x].adjacentBombsCount())
    {
      // Automatically discovers top-left neighbor:
      if ((y > 0) && (x > 0) && (!_map[y-1][x-1].isKnown()))
      {
        discover(y-1, x-1);
      }

      // Automatically discovers top neighbor:
      if ((y > 0) && (!_map[y-1][x].isKnown()))
      {
        discover(y-1, x);
      }

      // Automatically discovers top-right neighbor:
      if ((y > 0) && (x < _width-1) && (!_map[y-1][x+1].isKnown()))
      {
        discover(y-1, x+1);
      }

      // Automatically discovers left neighbor:
      if ((x > 0) && (!_map[y][x-1].isKnown()))
      {
        discover(y, x-1);
      }

      // Automatically discovers right neighbor:
      if ((x < _width-1) && (!_map[y][x+1].isKnown()))
      {
        discover(y, x+1);
      }

      // Automatically discovers bottom-left neighbor:
      if ((y < _height-1) && (x > 0) && (!_map[y+1][x-1].isKnown()))
      {
        discover(y+1, x-1);
      }

      // Automatically discovers bottom neighbor:
      if ((y < _height-1) && (!_map[y+1][x].isKnown()))
      {
        discover(y+1, x);
      }

      // Automatically discovers bottom-right neighbor:
      if ((y < _height-1) && (x < _width-1) && (!_map[y+1][x+1].isKnown()))
      {
        discover(y+1, x+1);
      }
    }
  }
}

void Board::addMines(int totalMines)
{
  Log::TRACE() << "Entering the Board::addMines() method...";
  Log::DEBUG() << "[Board] Adding " << totalMines << " mines.";
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> randy(0, _height - 1);
  std::uniform_int_distribution<int> randx(0, _width - 1);

  // Crops the totalMines in range: <1, (_width * _height)-1>:
  totalMines = std::max(totalMines, 1);
  totalMines = std::min(totalMines, (_width * _height) - 1);

  int minesPlaced = 0;
  while (minesPlaced < totalMines)
  {
    int y = randy(rng);
    int x = randx(rng);
    if (!_map[y][x].isBomb())
    {
      _map[y][x].setIsBomb(true);
      minesPlaced += 1;
      Log::VERBOSE() << "[Board] Bomb planted at (" << y << ", " << x << ").";
    }
  }
}

void Board::newGame(int totalMines)
{
  Log::TRACE() << "Entering the Board::newGame() method...";
  clear();
  addMines(totalMines);
  _totalMines = totalMines;
  calculateAdjacentBombsCount();
}

void Board::cycleFlag(int y, int x)
{
  Log::TRACE() << "Entering the Board::cycleFlag() method...";
  if (_map[y][x].isKnown())
  {
    // Does not allow putting flags on the fields that are already known:
    Log::VERBOSE() << "[Board] The tile: (" << y << ", " << x <<
        ") is already known - flags are not cycled.";
    return;
  }

  FlagCode fc = _map[y][x].flagCode();
  switch (fc)
  {
    case FlagCode::Empty :
      _map[y][x].setFlagCode(FlagCode::Mine);
      break;
    case FlagCode::Mine :
      _map[y][x].setFlagCode(FlagCode::Unknown);
      break;
    case FlagCode::Unknown :
      _map[y][x].setFlagCode(FlagCode::Empty);
      break;

    default:
      Log::WARNING() <<
          "Unrecognized flag encountered while trying to cycle flags.";
      break;
  }
}

GameState Board::state()
{
  return _state;
}

#include <iostream>
void Board::print()
{
  for(int h = 0; h < _height; ++h)
  {
    for(int w = 0; w < _width; ++w)
    {
      std::cout << _map[h][w].adjacentBombsCount() << "\t";
    }
    std::cout << std::endl;
  }
}
