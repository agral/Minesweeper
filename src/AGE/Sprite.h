#ifndef AGE_SPRITE_H
#define AGE_SPRITE_H

#include <SDL.h>


namespace AGE
{

class Sprite
{
 public:
  /**
   * Initializes a new instance of the Sprite class.
   *
   * \post A new instance of the Sprite class is created.
   *       It has both _texture and _renderer fields set to nullptr
   *       and _width and _height fields to 0.
   */
  Sprite();

  /**
   * Disposes of an instance of the Sprite class.
   *
   * \post The resources are disposed of by calling free() subroutine.
   */
  ~Sprite();

  /**
   * Loads the texture from a provided file and associates it with
   * the specified SDL_Renderer.
   *
   * If the Sprite already contains some data, they will all be erased.
   *
   * \param path The path to the image file that will be converted
   *        to the SDL_Texture.
   * \param renderer The SDL_Renderer that will be used for rendering
   *        this instance of SDL_Texture.
   * \post The instance has its _texture field pointing to a properly
   *        allocated resource, while both _width and _height fields
   *        contain proper values.
   * \return true if the texture has been loaded correctly.
   */
  bool loadFromFile(const char *path, SDL_Renderer *renderer);

  /**
   * Destroys the texture, thereby deallocating the dynamically managed
   * resources.
   *
   * \post * The underlying texture is destroyed by an appropriate SDL call,
   *       * the _texture pointer is set to nullptr,
   *       * both _width and _height fields' values are set to 0.
   */
  void free();

  /**
   * Renders the Sprite at the specified position, clipped to the requested
   * size, rotated by the requested angle along the requested anchor and
   * flipped according to the specified settings.
   *
   * \param x The position at which the sprite will be rendered
   *        along X axis, in pixels.
   * \param y The position at which the sprite will be rendered
   *        along Y axis, in pixels.
   * \param clip The rectangle clipping the Sprite to the requested dimensions,
   *        as SDL_Rect structure. By default there is no clipping.
   * \param angle An angle by which the rendered texture will be rotated
   *        clockwise, in degrees.
   * \param center The anchor around which the texture will be rotated,
   *        as a pointer to the SDL_Point structure.
   * \param flip The flip mode, expressed as a value in SDL_RendererFlip enum.
   *
   * \post The sprite is rendered.
   */
  void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
      SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

  /**
   * Returns the width of the texture in pixels.
   *
   * \return an int value representing the underlying texture width in pixels.
   */
  int width();

  /**
   * Returns the height of the texture in pixels.
   *
   * \return an int value representing the underlying texture height in pixels.
   */
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
   * Holds the width of the texture in pixels.
   */
  int _width;

  /**
   * Holds the height of the texture in pixels.
   */
  int _height;
};



} // namespace AGE

#endif // AGE_SPRITE_H
