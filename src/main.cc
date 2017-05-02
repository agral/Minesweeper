#include "Logger.h"

#include "AGE/Engine.h"

int main()
{
  AGE::Engine engine;

  Logger::instance().log(Logger::INFO, "Initializing...\n");
  if (!engine.init())
  {
    printf("Advanced Game Engine failed to initialize. Exiting.\n");
    exit(1);
  }

  Logger::instance().log(Logger::INFO, "Initialization complete.\nLoading the media...\n");
  if (!engine.loadMedia())
  {
    Logger::instance().log(Logger::WARNING, "Warning: some media files failed to load!\n");
  }
  Logger::instance().log(Logger::INFO, "Media loded.\n");

  engine.startLoop();

  // Destroys the window and quits the SDL system:
  engine.close();
  return 0;
}
