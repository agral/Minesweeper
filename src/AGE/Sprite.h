#ifndef AGE_SPRITE_H
#define AGE_SPRITE_H

#include <SDL.h>


namespace AGE
{

class Sprite
{
 public:
  Sprite();
  ~Sprite();

  bool loadFromFile(const char *path, SDL_Renderer *renderer);
  void free();
  void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
      SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

  int width();
  int height();

 private:
  /**
   * Holds the actual texture.
   */
  SDL_Texture *_texture;

  /**
   * Holds the renderer that will handles the texture.
   */
  SDL_Renderer *_renderer;

  /**
   * Returns the width of the texture in pixels.
   */
  int _width;

  /**
   * Returns the height of the texture in pixels.
   */
  int _height;
};



} // namespace AGE

#endif // AGE_SPRITE_H
