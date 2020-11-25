#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <utils.h>
#include <InputHandler.h>

/* should implement isRenderable or something like that */

class player
{
  /*properties*/
  public:
    int width = 300;
    int height = 300;
    int vel = 20;
    int bup;
    SDL_KeyCode up, down, left, right;
    float acc;

  /* private: */
    int posx, posy;
    int velx, vely;
    int accx, accy;

    /*methods*/
  public:
    player(int x);

    //needs & because events should be changeable
    void handleEvent(SDL_Event& e);
    void move();
    void render();
    void keyConfig(SDL_KeyCode, SDL_KeyCode, SDL_KeyCode, SDL_KeyCode);
    /* void simulate(); */
    void simulate();

  private:
    SDL_Rect mCollider;

};

