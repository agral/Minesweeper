enum class FlagCode
{
  Empty = 0,
  Mine,
  Unknown,
};

class Field
{
 public:
  Field();
  void clear();

 public:
  FlagCode _flagCode;
  bool _isBomb;
  bool _isKnown;
};



