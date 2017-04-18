enum class FlagCode
{
  Empty = 0,
  Mine,
  Unknown,
};

class Field
{
 public:
  /**
   * Generates a Field with FlagCode::Empty flag code
   * and with _isBomb and _isKnown flags set to false.
   *
   * \post Generated Field has:
   *    - _adjacentBombsCount set to 0,
   *    - _flagCode set to FlagCode::Empty,
   *    - _isBomb and _isKnown set to false.
   */
  Field();

  /**
   * Gets the value of _adjacentBombsCount field.
   *
   * \return value of _adjacentBombsCount field.
   */
  int adjacentBombsCount();

  /**
   * Sets the value of _adjacentBombsCount field.
   *
   * \param adjacentBombsCount new value of _adjacentBombsCount field.
   * \post this Field instance has _adjacentBombsCount value
   *     set to adjacentBombsCount.
   */
  void setAdjacentBombsCount(int adjacentBombsCount);

  /**
   * Gets the value of this Field instance's flag code.
   *
   * \return value of _flagCode of this Field instance.
   */
  FlagCode flagCode();

  /**
   * Sets new flag code.
   *
   * \post this Field instance has _flagCode set to flagCode.
   */
  void setFlagCode(FlagCode flagCode);

  /**
   * Gets the value of _isBomb flag.
   *
   * \return value of _isBomb flag of this Field instance.
   */
  bool isBomb();

  /**
   * Sets the value of _isBomb flag.
   *
   * \post this Field instance has _isBomb flag set to isBomb.
   */
  void setIsBomb(bool isBomb);

  /**
   * Gets the value of _isKnown flag.
   *
   * \return value of _isKnown flag of this Field instance.
   */
  bool isKnown();

  /**
   * Sets the value of _isKnown flag.
   *
   * \post this Field instance has _isKnown flag set to isKnown.
   */
  void setIsKnown(bool isKnown);

  /**
   * Clears a Field so that it has the same state as after its initialization.
   *
   * \post This Field instance has:
   *    - _adjacentBombsCount set to 0,
   *    - _flagCode set to FlagCode::Empty,
   *    - _isBomb and _isKnown set to false.
   */
  void clear();

 private:
  int _adjacentBombsCount;
  FlagCode _flagCode;
  bool _isBomb;
  bool _isKnown;
};
