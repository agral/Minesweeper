#include "SdlFunctions.h"

#include "Globals.h"

#include <SDL_image.h> // for IMG_Load() method
#include <cstdio>

namespace AGE
{

SDL_Surface* loadSurface(const char *path, bool critical)
{
  SDL_Surface *optimizedSurface = nullptr;
  SDL_Surface *loadedSurface = IMG_Load(path);
  if (nullptr == loadedSurface)
  {
    // @TODO: Logger class would be preferred.
    printf("Unable to load image [%s].\nSDL_image error: %s\n",
        path, IMG_GetError());
    if (critical)
    {
      exit(2);
    }

    return nullptr;
  }
  else
  {
    optimizedSurface = SDL_ConvertSurface(loadedSurface,
        screenSurface->format, 0);
    if (nullptr == optimizedSurface)
    {
      // @TODO: better logging.
      printf("Unable to optimize surface for image [%s].\nSDL error: %s\n",
          path, SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
  }
}

} // namespace AGE
