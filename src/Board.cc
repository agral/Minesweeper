#include "Board.h"
#include <random>
#include <iostream>

Board::Board(int width, int height) :
  _width(width),
  _height(height)
{
  _map.resize(height);
  for(int h = 0; h < height; ++h)
  {
    _map[h].resize(width);
  }
}

std::string Board::peekAtField(int x, int y)
{
  // Not implemented.
  return "Not implemented";
}

int Board::width()
{
  return _width;
}

int Board::height()
{
  return _height;
}

void Board::clear()
{
  for(int h = 0; h < _height; ++h)
  {
    for(int w = 0; w < _width; ++w)
    {
      _map[h][w].clear();
    }
  }
}

void Board::calculateAdjacentBombCounts()
{
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

void Board::addMines(int totalMines)
{
  std::cout << "Adding " << totalMines << " mines." << std::endl;
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> randx(0, _width - 1);
  std::uniform_int_distribution<int> randy(0, _height - 1);

  // Crops the totalMines in range: <1, (_width * _height)-1>:
  totalMines = std::max(totalMines, 1);
  totalMines = std::min(totalMines, (_width * _height) - 1);

  int minesPlaced = 0;
  while (minesPlaced < totalMines)
  {
    int x = randx(rng);
    int y = randy(rng);
    if (!_map[x][y].isBomb())
    {
      _map[x][y].setIsBomb(true);
      minesPlaced += 1;
    }
  }
}

void Board::newGame(int totalMines)
{
  clear();
  addMines(totalMines);
  calculateAdjacentBombCounts();
}

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
