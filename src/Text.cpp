#include <Text.h>

Text::Text() {
  Texture gTextTexture;
  gFont = TTF_OpenFont("lazy.ttf", 28);
  SDL_Color textColor = {255, 255, 255};
}

Text::~Text() {
}


/* void Text::printText(std::string actualText = "null", SDL_Renderer* tRenderer) { */
/*   std::cout << this->actualText << std::endl; */
/*   this->loadFromRenderedText("cock", textColor, tRenderer); */
/* } */

bool Text::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* tRenderer)
{
  texture.free();

  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

  texture.mTexture = SDL_CreateTextureFromSurface(tRenderer, textSurface);

  texture.mWidth = textSurface->w;
  texture.mHeight = textSurface->h;

  SDL_FreeSurface(textSurface);

  return texture.mTexture !=NULL;
}


