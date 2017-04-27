#include "Sprite.h"

#include <SDL_image.h>
#include <cstdio>


namespace AGE
{

Sprite::Sprite() :
  _texture(nullptr),
  _renderer(nullptr),
  _width(0),
  _height(0)
{
  // All the work is done in the initializer.
}


Sprite::~Sprite()
{
  free();
}


bool Sprite::loadFromFile(const char *path, SDL_Renderer *renderer)
{
  // Disposes of previous texture, if there was any:
  if (nullptr != _texture)
  {
    free();
  }

  if (nullptr == renderer)
  {
    printf("Error: Can not assign a null renderer to texture <%s>.\n", path);
    return false;
  }
  _renderer = renderer;

  SDL_Surface *surface = IMG_Load(path);
  if (nullptr == surface)
  {
    printf("Image <%s> could not be loaded.\n"
           "SDL error: %s\n", path, SDL_GetError());
  }
  else
  {
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (nullptr == _texture)
    {
      printf("Unable to create texture from <%s>.\n"
             "SDL error: %s\n", path, SDL_GetError());
    }
    else
    {
      _width = surface->w;
      _height = surface->h;
    }

    SDL_FreeSurface(surface);
  }

  return (nullptr != _texture);
}


void Sprite::free()
{
  if (nullptr != _texture)
  {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _width = 0;
    _height = 0;
  }
}


void Sprite::render(int x, int y, SDL_Rect *clip, double angle,
    SDL_Point *center, SDL_RendererFlip flip)
{
  // Sets target bounding box, using full texture geometry:
  SDL_Rect targetBox = {x, y, _width, _height};

  // If the texture is clipped, target bounding box needs to reflect this:
  if (nullptr != clip)
  {
    targetBox.w = clip->w;
    targetBox.h = clip->h;
  }

  // Finally renders the texture on screen:
  SDL_RenderCopyEx(_renderer, _texture, clip, &targetBox, angle, center, flip);
}


int Sprite::width()
{
  return _width;
}


int Sprite::height()
{
  return _height;
}

} // namespace AGE
