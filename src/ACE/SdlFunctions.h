#ifndef AGE_SDLFUNCTIONS_H
#define AGE_SDLFUNCTIONS_H

#include <SDL.h> // for SDL_Surface declaration


namespace AGE
{

extern SDL_Surface* loadSurface(const char *path, bool critical=true);

} // namespace AGE

#endif // AGE_SDLFUNCTIONS_H
