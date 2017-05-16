#include "Log/Logger.h"
#include "AGE/Engine.h"

int main()
{
  // A block defining the lifetime of all the game objects:
  {
    Log::TRACE() << "Starting the main method.";
    Log::DEBUG() << "Creating the AGE::Engine...";
    AGE::Engine engine;

    Log::DEBUG() << "Initializing the game engine...";
    if (!engine.init())
    {
      Log::FATAL() << "Advanced Game Engine failed to initialize. Exiting.";
      exit(1);
    }

    Log::DEBUG() << "Game engine initialization complete.";
    Log::DEBUG() << "Loading the media...";
    if (!engine.loadMedia())
    {
      Log::WARNING() << "Warning: some media files failed to load.";
    }
    Log::VERBOSE() << "Media loded.";

    Log::DEBUG() << "Starting the game engine's loop.";
    engine.startLoop();

    // Destroys the window and quits the SDL system:
    Log::DEBUG() << "Closing the game engine.";
    engine.close();
  }

  Log::DEBUG() << "Terminating - bye!";
  return 0;
}
