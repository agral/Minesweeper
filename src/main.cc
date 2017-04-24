#include <cstdio>

#include "Board.h"
#include "AGE/Engine.h"

int main()
{
  AGE::Engine engine;

  printf("Initializing...\n");
  if (!engine.init())
  {
    printf("Advanced Game Engine failed to initialize. Exiting.\n");
    exit(1);
  }

  printf("Initialization complete.\nLoading the media...\n");
  if (!engine.loadMedia())
  {
    printf("Warning: some media files failed to load!\n");
  }
  printf("Media loded.\n");

  engine.startLoop();

  // Destroys the window and quits the SDL system:
  engine.close();
  return 0;
}
