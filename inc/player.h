#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <utils.h>
#include <InputHandler.h>
#include <Vector2D.h>

/* should implement isRenderable or something like that */

class player
{
  /*properties*/
  public:
    const int playerWidth = 2;
    const int playerHeight = 300;
    int vel;
    int bup;
    SDL_Scancode up, down;
    float acc;

  /* private: */
    float posx, posy;
    float velx, vely;
    float accx, accy;


  Vector2D accV(float accx,float  accy);
  Vector2D velV(float velx,float  vely);
  Vector2D posV(float posx, float posy);
    /*methods*/
  public:
    player();

    //needs & because events should be changeable
    void handleEvent(SDL_Event& e);
    void move();
    void render();
    void keyConfig(SDL_Scancode, SDL_Scancode);
    /* void simulate(); */
    void simulate();
    void keyConf(SDL_Scancode);

    void setAccn(float x, float y);

  private:
    SDL_Rect mCollider;
    void arenaCollision();

};

