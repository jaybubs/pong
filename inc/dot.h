#pragma once
#include <SDL.h>

class Dot
{
  public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 20;
    Dot ();
    //needs & e because events should be changeable
    void move();
    void render();

  /* private: */
    float mposx, mposy;
    float mvelx, mvely;
    SDL_Rect mCollider;
};
