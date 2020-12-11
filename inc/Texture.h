#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Texture
{
  public:
    Texture();
    ~Texture();

    friend class Text;

    bool loadFromFile(std::string pat, SDL_Renderer* tRenderer);

		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string if SDL TTF module is loaded
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* tRenderer);
		#endif

    //dealloc texture
    void free();

    //set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //set blending
    void setBlendMode(SDL_BlendMode blending);

    //set alpha modulation
    void setAlpha(Uint8 alpha);

    //renders texture at a given ponit
    void render(
        int x,
        int y,
        SDL_Renderer* tRenderer = NULL,
        SDL_Rect* clip = NULL,
        double angle = 0.0,
        SDL_Point* center = NULL,
        SDL_RendererFlip flip = SDL_FLIP_NONE
        );

    //get img dimensions
    int getWidth();
    int getHeight();

  private:
    //the actual hw texture
    SDL_Texture* mTexture;

    //img dimensions
    int mWidth;
    int mHeight; 
};
