#include "catch.hpp"
#include "../src/Board.h"

TEST_CASE("Board class tests", "[Board]")
{
  SECTION("The constructor properly sets width and height of the board")
  {
    const int desired_width = 11;
    const int desired_height = 12;
    Board b(desired_height, desired_width);
    REQUIRE(desired_height == b.height());
    REQUIRE(desired_width == b.width());
  }
}
