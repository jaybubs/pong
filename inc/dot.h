#pragma once
#include <SDL.h>
#include <Texture.h>
#include <Score.h>

class Dot
{
  public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 20;
    Dot ();
    Texture gDotTexture;
    //needs & e because events should be changeable
    void move();
    void render(SDL_Renderer* gRenderer);
    bool loadMedia(SDL_Renderer* gRenderer);
    Score score;

  /* private: */
    float mposx, mposy;
    float mvelx, mvely;
    SDL_Rect mCollider;
};
