#include "Board.h"
#include <random>
#include <iostream>

Board::Board(int width, int height) :
  _width(width),
  _height(height)
{
  // Not implemented.
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

std::string peekAtField(int x, int y)
{
  // @TODO implement me.
}

void Board::fillRandomly(int totalMines)
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> randx(0, _width - 1);
  std::uniform_int_distribution<int> randy(0, _height - 1);

  for(int b = 0; b < totalMines; ++b)
  {
    int x = randx(rng);
    int y = randy(rng);
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }
}
