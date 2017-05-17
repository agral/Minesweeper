#include "../Log/Logger.h"
#include "Sprite.h"

#include <SDL_image.h>


namespace AGE
{

Sprite::Sprite() :
  _texture(nullptr),
  _renderer(nullptr),
  _width(0),
  _height(0)
{
  Log::TRACE() << "Entering the Sprite class constructor...";

  // All the work is done in the initializer.
}


Sprite::~Sprite()
{
  Log::TRACE() << "Entering the Sprite class destructor...";
  free();
}


bool Sprite::loadFromFile(const char *path, SDL_Renderer *renderer)
{
  Log::TRACE() << "Entering the Sprite::loadFromFile() method...";

  // Disposes of previous texture, if there was any:
  if (nullptr != _texture)
  {
    free();
  }

  if (nullptr == renderer)
  {
    Log::ERROR() << "Can not assign a null renderer to the texture" << path;
    return false;
  }
  _renderer = renderer;

  Log::DEBUG() << "Loading the surface: [" << path << "] ...";
  SDL_Surface *surface = IMG_Load(path);
  if (nullptr == surface)
  {
    Log::ERROR() << "Image [" << path << "] could not be loaded.";
    Log::ERROR() << "SDL error: " << SDL_GetError();
  }
  else
  {
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (nullptr == _texture)
    {
      Log::ERROR() << "Unable to create texture from [" << path << "].";
      Log::ERROR() << "SDL error: " << SDL_GetError();
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
  Log::TRACE() << "Entering the Sprite::free() method...";
  if (nullptr != _texture)
  {
    Log::DEBUG() << "Freeing the texture " << _texture;
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _width = 0;
    _height = 0;
  }
}


void Sprite::render(int x, int y, SDL_Rect *clip, double angle,
    SDL_Point *center, SDL_RendererFlip flip)
{
  Log::TRACE() << "Entering the Sprite::render() method...";
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

} // namespace AGE
