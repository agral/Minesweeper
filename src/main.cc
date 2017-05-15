#include "Logger/Logger.h"

#include "AGE/Engine.h"

int main()
{
  Log::VERBOSE() << "Starting the main method.";
  Log::DEBUG() << "Creating the AGE::Engine...";
  AGE::Engine engine;

  Log::DEBUG() << "Initializing the AGE::Engine...";
  if (!engine.init())
  {
    // Logger::instance().log(Logger::CRITICAL,
        // "Advanced Game Engine failed to initialize. Exiting.");
    exit(1);
  }

  // Logger::instance().log(Logger::INFO, "Initialization complete.");
  // Logger::instance().log(Logger::INFO, "Loading the media...");
  if (!engine.loadMedia())
  {
    // Logger::instance().log(Logger::WARNING,
        // "Warning: some media files failed to load!");
  }
  // Logger::instance().log(Logger::INFO, "Media loded.");

  engine.startLoop();

  // Destroys the window and quits the SDL system:
  engine.close();
  return 0;
}
