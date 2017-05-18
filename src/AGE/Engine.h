#ifndef AGE_ENGINE_H
#define AGE_ENGINE_H

#include "../Board.h"

namespace AGE
{

class Engine
{
 public:
  Engine();
  ~Engine();

  bool init();
  bool loadMedia();

  void startLoop();
  void close();

 private:
  void draw();

 private:
  bool _isInitialized;
  bool _isClosed;

  int _boardOffsetY;
  int _boardOffsetX;
  int _boardWidthPx;
  int _boardHeightPx;

  Board _board;
};



} // namespace AGE

#endif // AGE_ENGINE_H
