#include "catch.hpp"
#include "../src/Board.h"

TEST_CASE("Board class tests", "[Board]")
{
  SECTION("Constructor correctly sets width and height")
  {
    const int w = 11;
    const int h = 12;
    Board b(w, h);
    REQUIRE(b.width() == w);
    REQUIRE(b.height() == h);
  }
}
