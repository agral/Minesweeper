#include "Field.h"

#include <string>

Field::Field() :
  _adjacentBombsCount(0),
  _flagCode(FlagCode::Empty),
  _isBomb(false),
  _isKnown(false)
{
  // All the work is done in the initializer.
}

int Field::adjacentBombsCount()
{
  return _adjacentBombsCount;
}

void Field::setAdjacentBombsCount(int adjacentBombsCount)
{
  _adjacentBombsCount = adjacentBombsCount;
}

FlagCode Field::flagCode()
{
  return _flagCode;
}

void Field::setFlagCode(FlagCode flagCode)
{
  _flagCode = flagCode;
}

bool Field::isBomb()
{
  return _isBomb;
}

void Field::setIsBomb(bool isBomb)
{
  _isBomb = isBomb;
}

bool Field::isKnown()
{
  return _isKnown;
}

void Field::setIsKnown(bool isKnown)
{
  _isKnown = isKnown;
}

void Field::clear()
{
  _adjacentBombsCount = 0;
  _flagCode = FlagCode::Empty;
  _isBomb = false;
  _isKnown = false;
}

std::string Field::toString()
{
  std::string abc = std::to_string(_adjacentBombsCount);
  std::string fc;
  if (_flagCode == FlagCode::Empty)
  {
    fc = "Empty";
  }
  else if (_flagCode == FlagCode::Mine)
  {
    fc = "Mine";
  }
  else if (_flagCode == FlagCode::Unknown)
  {
    fc = "Unknown";
  }
  else
  {
    // Should not happen.
    fc += "Unrecognized!";
  }
  std::string isBomb = (_isBomb ? "true" : "false");
  std::string isKnown = (_isKnown ? "true" : "false");

  return (abc + "," + fc + "," + isBomb + "," + isKnown);
}
