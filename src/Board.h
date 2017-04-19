#ifndef BOARD_H
#define BOARD_H

#include "Field.h"
#include <vector>
#include <string>

class Board
{
 public:
  /**
   * Initializes a new instance of the Board class.
   *
   * \param width The width of a board in Field units.
   * \param height The height of a board in Field units.
   *
   * \post A new instance of the Board class is created.
   * It has width and height set to the appropriate values
   * and every Field constituting the board is in clear state
   * (see the Field documentation for more info).
   */
  Board(int width, int height);

 public:
  /**
   * Gets the value of the width of the board.
   *
   * \return the width of the board.
   */
  int width();

  /**
   * Gets the value of the height of the board.
   *
   * \return the height of the board.
   */
  int height();

  std::string peekAtField(int x, int y);

  /**
   * Fills the board randomly with a totalMines mines.
   *
   * In order to do this, the board is cleared first by calling clear(),
   * then the total of totalMines mines are placed at distinct random positions
   * on the board. Finally all the fields' _adjacentBombsCount parameter
   * gets updated.
   *
   * \param totalMines the total number of mines to be distributed at distinct
   * random positions on the board.
   *
   * \pre totalMines is in range: 0 < totalMines < (_width * _height).
   * \post The board has totalMines mines placed at random distinct locations.
   */
  void fillRandomly(int totalMines);

 private:
  int _width;
  int _height;
  std::vector< std::vector< Field > > _map;
};



#endif // BOARD_H
