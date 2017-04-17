#include "Board.h"

#include <iostream>

/// HELPER METHODS:
void Board::clear()
{
  for(int h = 0; h < _height; ++h)
  {
    for (int w = 0; w < _width; ++w)
    {
      _fields[h][w].clear();
    }
  }

  _totalMines = 0;
  _totalNormalFields = (_width * _height);
  _totalFields = _totalNormalFields;
  _discoveredFields = 0;
}

/// End of helper methods.

Board::Board(int width, int height) :
  _width(width),
  _height(height),
  _totalMines(0),
  _totalNormalFields(width * height),
  _totalFields(_totalNormalFields),
  _discoveredFields(0)
{
  _fields.resize(height);
  for(int y = 0; y < height; ++y)
  {
    _fields[y].resize(width);
  }

  // Clears the board, so that every field becomes undiscovered and empty:
  clear();
}

void Board::newGame(int totalMines)
{
  std::cout << "NewGame(" << totalMines << ")" << std::endl;
}
