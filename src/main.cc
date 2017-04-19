#include <iostream>

#include "Board.h"

int main()
{
  Board b(10, 10);
  b.fillRandomly(10);


  std::cout << "main executed" << std::endl;
  return 0;
}
