#pragma once
#include <Texture.h>

Texture::Texture() //constructor
{
  //init
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture()
{
  //dealloc
  free();
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* tRenderer = NULL)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( tRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif 

bool Texture::loadFromFile(std::string path, SDL_Renderer* tRenderer = NULL)
{
  //get rid of existing texture
  free();

  //final texture
  SDL_Texture* newTexture = NULL;

  //load img
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  //color key
  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
  //create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface(tRenderer, loadedSurface);
  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
  return mTexture != NULL;
}

void Texture::free()
{
  //free if exists
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  //modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
  //set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
  //modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer* tRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  //set rendering space and render to screen
  SDL_Rect renderQuad = {x,y,mWidth,mHeight};
  //set clip rendering dims
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //render to screen
  SDL_RenderCopyEx(tRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
  return mWidth;
}
int Texture::getHeight()
{
  return mHeight;
}
