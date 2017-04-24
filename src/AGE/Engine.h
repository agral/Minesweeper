#ifndef AGE_ENGINE_H
#define AGE_ENGINE_H

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
  bool _isInitialized;
  bool _isClosed;
  /* code */
};



} // namespace AGE

#endif // AGE_ENGINE_H
