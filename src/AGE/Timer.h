#include <SDL.h>

namespace AGE
{

class Timer
{
 public:
  /**
   * Initializes a new instance of the Timer class.
   *
   * \post A new instance of the Timer class is created, cleared and put into
   *       a stopped state.
   */
  Timer();

  /**
   * Starts the timer.
   *
   * \post The timer changes its state to started.
   */
  void start();

  /**
   * Stops the timer.
   *
   * \post The timer changes its state to stopped and resets.
   *
   * \remarks After the timer stops, all its values are reset, so the callee
   *          should read the measurements before stopping the timer.
   */
  void stop();

  /**
   * Pauses the timer.
   *
   * Upon calling this function, the timer changes its state from started
   * to paused.
   *
   * \pre The timer is in a started state.
   * \post The timer is in a paused state.
   */
  void pause();

  /**
   * Resumes the paused timer.
   *
   * Upon calling this function, the timer changes its state from paused
   * to started.
   *
   * \pre The timer is in a paused state.
   * \post The timer is in a started state.
   */
  void resume();

  /**
   * Gets the elapsed time expressed in milliseconds.
   *
   * \return An unsigned 32-bit value
   *         representing the elapsed time expressed in milliseconds
   */
  Uint32 ticks();

  /**
   * Checks whether the timer is paused.
   *
   * \return true if this instance is in a paused state.
   */
  bool paused() { return _paused; }

  /**
   * Checks whether the timer is started (active).
   *
   * \return true if this instance is in a started (active) state.
   */
  bool started() { return _started; }

 private:
   Uint32 _startTicks;
   Uint32 _pausedTicks;
   bool _paused;
   bool _started;
};

} // namespace AGE
