#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <InputHandler.h>
#include <player.h>
#include <dot.h>
#include <Collision.h>
#include <Texture.h>
#include <utils.h>




bool initialiseSDL();
bool loadMedia();
void killSDL();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* tRenderer = NULL;
TTF_Font* gFont = NULL;

/* Texture gTextTexture; */

bool initialiseSDL()
{
  //initalisation flag
  bool success = true;

  //init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("warning linear texture filtering not enabled!\n");
    }
    //create window
    gWindow = SDL_CreateWindow("SDL TUT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, utils::screenW, utils::screenH, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("renderer could not be created sdl error: %s\n", SDL_GetError());
        success = false;
      } else {


        //initialise renderer colour
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //initalise png loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialise! SDL_image error: %s\n", IMG_GetError());
          success = false;
        }
        //init ttf
        if (TTF_Init() == -1) {
          printf("sdl ttf could not initialise %s\n", TTF_GetError());
          success = false;
        }
      }
    } 
  }

  return success;
}

void killSDL()
{
  TTF_CloseFont(gFont);
  gFont = NULL;

  //destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  //quit SDL
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[]) //required by SDL
{

  if (!initialiseSDL()) {
    printf("Failed to initialise\n");
  } else {
      //main loop flag
      bool quit = false;

      //event handler

      _InputHandler::Instance()->init();
      /* input.handleKeyboardEvent(&e); */

      //object
      Dot dot;
      dot.loadMedia(gRenderer);
      player p1;
      /* init p1 on RHS and VV */
      p1.posx = 0.9*utils::screenW;
      p1.keyConfig(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
      player p2;
      p2.posx = 0.1*utils::screenW;
      p2.keyConfig(SDL_SCANCODE_W, SDL_SCANCODE_S);

      /* instead of loading textures, only simple lines will be rendered */
      SDL_Rect p1box;
      SDL_Rect p2box;
      //text color
      SDL_Color textColor = {0,0,0,255};
      //text color

      Collision collide;

      //while app is running
      while (!_InputHandler::Instance()->quit) {
        //handle input and events in the queue
        _InputHandler::Instance()->update();
        p1.move();
        p1.simulate();

        p2.move();
        p2.simulate();

        dot.move();

        /* dot-player collision, needs two if blocks because of relative positions of players */
        if (
            collide.aabbaabb(
              dot.mposx, dot.mposy, dot.DOT_WIDTH, dot.DOT_HEIGHT,
              p1.posx, p1.posy, p1.playerWidth, p1.playerHeight)
           ) {
          dot.mposx = p1.posx - p1.playerWidth/2 - dot.DOT_WIDTH;
          dot.mvelx *= -1;
          dot.mvely = (dot.mposy - p1.posy - (p1.playerHeight/2))*2 + p1.vely * .9f;
        } 

        if (
            collide.aabbaabb(
              p2.posx, p2.posy, p2.playerWidth, p2.playerHeight, 
              dot.mposx, dot.mposy, dot.DOT_WIDTH, dot.DOT_HEIGHT)
           ) {
          dot.mposx = p2.posx + p2.playerWidth/2 + dot.DOT_WIDTH;
          dot.mvelx *= -1;
          dot.mvely = (dot.mposy - p2.posy - (p2.playerHeight/2))*2 + p2.vely * .9f;
        } 
        //clear screen
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_RenderClear(tRenderer);


        //dot collision box
        SDL_Rect rectangle;
        rectangle.x = dot.mposx;
        rectangle.y = dot.mposy;
        rectangle.w = dot.DOT_WIDTH;
        rectangle.h = dot.DOT_HEIGHT;

        //render players
        p1box.x = p1.posx;
        p1box.y = p1.posy;
        p1box.w = p1.playerWidth;
        p1box.h = p1.playerHeight;

        p2box.x = p2.posx;
        p2box.y = p2.posy;
        p2box.w = p2.playerWidth;
        p2box.h = p2.playerHeight;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0x00);
        SDL_RenderDrawRect(gRenderer, &p1box);
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0x00);
        SDL_RenderDrawRect(gRenderer, &p2box);

        dot.render(gRenderer);
        dot.score.display(tRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderDrawRect(gRenderer, &rectangle);

        //update screen
        SDL_RenderPresent(gRenderer);
      }

    }

  killSDL();

  return 0;
}
