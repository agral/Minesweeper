#include "catch.hpp"
#include "../src/Field.h"

TEST_CASE("Field class tests", "[Field]")
{
  SECTION("Getter/Setter of _adjacentBombsCount works properly")
  {
    Field f;
    f.setAdjacentBombsCount(3);
    REQUIRE(3 == f.adjacentBombsCount());
  }

  SECTION("Getter/Setter of _flagCode field works properly")
  {
    Field f;
    f.setFlagCode(FlagCode::Empty);
    REQUIRE(f.flagCode() == FlagCode::Empty);
    f.setFlagCode(FlagCode::Mine);
    REQUIRE(f.flagCode() == FlagCode::Mine);
    f.setFlagCode(FlagCode::Unknown);
    REQUIRE(f.flagCode() == FlagCode::Unknown);
  }

  SECTION("Getter/Setter of _isBomb field works properly")
  {
    Field f;
    f.setIsBomb(true);
    REQUIRE(f.isBomb() == true);
    f.setIsBomb(false);
    REQUIRE(f.isBomb() == false);
  }

  SECTION("Getter/Setter of _isKnown field works properly")
  {
    Field f;
    f.setIsKnown(true);
    REQUIRE(f.isKnown() == true);
    f.setIsKnown(false);
    REQUIRE(f.isKnown() == false);
  }

  SECTION("Constructor correctly pre-initializes the values"
      " in accordance with the specification")
  {
    // The specs require that after Field construction the fields
    // are initialized to the following values:
    const int expectedAdjacentBombsCount = 0;
    const FlagCode expectedFlagCode = FlagCode::Empty;
    const bool expectedIsBomb = false;
    const bool expectedIsKnown = false;

    Field f;
    REQUIRE(f.adjacentBombsCount() == expectedAdjacentBombsCount);
    REQUIRE(f.flagCode() == expectedFlagCode);
    REQUIRE(f.isBomb() == expectedIsBomb);
    REQUIRE(f.isKnown() == expectedIsKnown);
  }

  SECTION("Calling clear() results in instance fields "
      "being set to proper values")
  {
    const int expectedAdjacentBombsCount = 0;
    const FlagCode expectedFlagCode = FlagCode::Empty;
    const bool expectedIsBomb = false;
    const bool expectedIsKnown = false;

    Field f;
    f.setAdjacentBombsCount(5);
    f.setFlagCode(FlagCode::Unknown);
    f.setIsBomb(!expectedIsBomb);
    f.setIsKnown(!expectedIsKnown);

    f.clear();
    REQUIRE(f.adjacentBombsCount() == expectedAdjacentBombsCount);
    REQUIRE(f.flagCode() == expectedFlagCode);
    REQUIRE(f.isBomb() == expectedIsBomb);
    REQUIRE(f.isKnown() == expectedIsKnown);
  }

  SECTION("toString() method generates proper strings")
  {
    // Require that two fields with different parameters
    // result in different strings:
    Field a;
    a.setAdjacentBombsCount(5);
    a.setFlagCode(FlagCode::Unknown);
    a.setIsBomb(true);
    a.setIsKnown(false);
    Field b;
    b.setAdjacentBombsCount(3);
    b.setFlagCode(FlagCode::Empty);
    b.setIsBomb(false);
    b.setIsKnown(true);
    REQUIRE(a.toString() != b.toString());

    // Require that two fields with the same parameters
    // result in the same string:
    Field c;
    c.setAdjacentBombsCount(5);
    c.setFlagCode(FlagCode::Unknown);
    c.setIsBomb(true);
    c.setIsKnown(false);
    REQUIRE(a.toString() == c.toString());

    // Require that a cleared field has the same textual representation
    // as a fresh one:
    Field d;
    a.clear();
    REQUIRE(a.toString() == d.toString());
  }
}
