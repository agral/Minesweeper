#include "Timer.h"
#include "../Log/Logger.h"

namespace AGE
{

Timer::Timer() :
  _startTicks(0),
  _pausedTicks(0),
  _paused(false),
  _started(false)
{
  // All the work is done in the initialization block.
}


void Timer::start()
{
  _paused = false;
  _started = true;

  _pausedTicks = 0;
  _startTicks = SDL_GetTicks();
}


void Timer::stop()
{
  _paused = false;
  _started = false;
  _pausedTicks = 0;
  _startTicks = 0;
}


void Timer::pause()
{
  if (_started && !_paused)
  {
    _paused = true;

    _pausedTicks = SDL_GetTicks() - _startTicks;
    _startTicks = 0;
  }
}


void Timer::resume()
{
  if (_started && _paused)
  {
    _paused = false;

    _startTicks = SDL_GetTicks() - _pausedTicks;
    _pausedTicks = 0;
  }
}


Uint32 Timer::ticks()
{
  Uint32 time = 0;
  if (_started)
  {
    time = (_paused ? _pausedTicks : SDL_GetTicks() - _startTicks);
  }

  return time;
}

} // namespace AGE
