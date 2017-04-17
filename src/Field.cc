#include "Field.h"

Field::Field() :
  _flagCode(FlagCode::Empty),
  _isBomb(false),
  _isKnown(false)
{
  // All the work is done in the initializer.
}

void Field::clear()
{
  _flagCode = FlagCode::Empty;
  _isBomb = false;
  _isKnown = false;
}
