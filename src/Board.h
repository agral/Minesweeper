#include <vector>      // std::vector
#include "Field.h"


class Board
{
 public:
  Board(int width, int height);
  void newGame(int totalMines);

  void discover(int X, int Y);
  void flagField(int X, int Y, int flagCode);

  // Getters:
  int width() { return _width; }
  int height() { return _height; }
  int totalMines() { return _totalMines; }

  // Debug methods:
  void print();

 private:
  // HELPER METHODS:
  void clear();

  // Fields:
  std::vector< std::vector< Field > > _fields;
  int _width;
  int _height;

  int _totalMines;
  // How many fields need to be discovered in order to win the game:
  int _totalNormalFields;
  int _totalFields;
  // How many fields have been discovered so far by the player:
  int _discoveredFields;
};


