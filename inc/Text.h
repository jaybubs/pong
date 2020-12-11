#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <Texture.h>
#include <iostream>
#include <string>

class Text
{
  /* properties */
  private:
    TTF_Font* gFont;
    SDL_Color textColor;

    /* methods */
  public:
    Text ();
    virtual ~Text ();

    Texture texture;
    std::string actualText;

    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* tRenderer);

    void printText(std::string actualText, SDL_Renderer* tRenderer);

};
