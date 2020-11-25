#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <InputHandler.h>
#include <player.h>
#include <utils.h>



//texture wrapper class
class LTexture
{
  public:
    //init variables
    LTexture();
    //deallocate mem
    ~LTexture();

    //loads img from path
    bool loadFromFile(std::string path);

		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
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
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

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

class LTimer
{
  public:
    LTimer ();

    //clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //timer's time
    Uint32 getTicks();

    //utils::check status
    bool isStarted();
    bool isPaused();

  private:
    //time when timer started
    Uint32 mStartTicks;
    //ticks stored when paused
    Uint32 mPausedTicks;
    //timer status
    bool mPaused;
    bool mStarted;
};

class Dot
{
  public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 20;
    Dot ();
    //needs & e because events should be changeable
    void handleEvent(SDL_Event& e);
    void move(SDL_Rect& wall);
    void render();

  private:
    int mposx, mposy;
    int mvelx, mvely;
    SDL_Rect mCollider;
};

bool initialiseSDL();
bool loadMedia();
void killSDL();
/* bool utils::checkCollision(SDL_Rect a, SDL_Rect b); */
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

//dot shit
Dot::Dot()
{
  mposx = 0;
  mposy = 0;
  mvelx = 10;
  mvely = 0;
  mCollider.w = DOT_WIDTH;
  mCollider.h = DOT_HEIGHT;
}

void Dot::handleEvent(SDL_Event& e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_UP: mvely    -= DOT_VEL; break;
      case SDLK_DOWN: mvely  += DOT_VEL; break;
      case SDLK_LEFT: mvelx  -= DOT_VEL; break;
      case SDLK_RIGHT: mvelx += DOT_VEL; break;
    }
  }
  if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_UP: mvely    += DOT_VEL; break;
      case SDLK_DOWN: mvely  -= DOT_VEL; break;
      case SDLK_LEFT: mvelx  += DOT_VEL; break;
      case SDLK_RIGHT: mvelx -= DOT_VEL; break;
    }
  }
}

void Dot::move(SDL_Rect& wall)
{
  mposx += mvelx;
  mCollider.x = mposx;
  if ((mposx < 0) || (mposx + DOT_WIDTH > utils::screenW) || utils::checkCollision(mCollider, wall)) {
    mposx -= mvelx;
    mCollider.x = mposx;
  }
  mposy += mvely;
  mCollider.y = mposy;
  if ((mposy < 0) || (mposy + DOT_HEIGHT > utils::screenH) || utils::checkCollision(mCollider, wall)) {
    mposy -= mvely;
    mCollider.y = mposy;
  }
}



LTexture gDotTexture;
void Dot::render()
{
  gDotTexture.render(mposx, mposy);
}

LTexture gPlayerTexture;
void player::render()
{
  gPlayerTexture.render(posx, posy);
}

//timer shit
LTimer::LTimer()
{
  //init the variables
  mStartTicks = 0;
  mPausedTicks = 0;
  mPaused = false;
  mStarted = false;
}

void LTimer::start()
{
  mStarted = true;

  mPaused = false;

  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

void LTimer::stop()
{
  mStarted = false;
  mPaused = false;
  mStartTicks = 0;
  mPausedTicks = 0;
}

void LTimer::pause()
{
  //if running but not paused
  if (mStarted && !mPaused) {
    mPaused = true;
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
  }
}

void LTimer::unpause()
{
  //if running and paused
  if (mStarted && mPaused) {
    mPaused = false;
    mStartTicks = SDL_GetTicks() - mPausedTicks;
    mPausedTicks =0;
  }
}

Uint32 LTimer::getTicks()
{
  //the actual timer time
  Uint32 time = 0;
  //if timer is running
  if (mStarted) {
    //if paused
    if (mPaused) {
      //return the no of tix when timer was paused
      time = mPausedTicks;
    } else {
      //return the curren time minus start time
      time = SDL_GetTicks() - mStartTicks;
    }
  }
  return time;
}
//access and utils::check status
bool LTimer::isStarted()
{
  return mStarted;
}
bool LTimer::isPaused()
{
  return mPaused && mStarted;
}

//texture shit
LTexture gTimeTextTexture;
LTexture gStartPromptTextTexture;
LTexture gPausePromptTextTexture;

LTexture::LTexture() //constructor
{
  //init
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture()
{
  //dealloc
  free();
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
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

bool LTexture::loadFromFile(std::string path)
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
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free()
{
  //free if exists
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  //modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
  //set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
  //modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  //set rendering space and render to screen
  SDL_Rect renderQuad = {x,y,mWidth,mHeight};
  //set clip rendering dims
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //render to screen
  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
  return mWidth;
}
int LTexture::getHeight()
{
  return mHeight;
}


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

bool loadMedia()
{
  bool success = true;

  gDotTexture.loadFromFile("dot.png");
  gPlayerTexture.loadFromFile("cry.png");
  SDL_Color textColor = {0,0,0,255};
  //no need to rerender a static texture every time so load once

  return success;
}
void killSDL()
{
  gTimeTextTexture.free();
  gStartPromptTextTexture.free();
  gPausePromptTextTexture.free();

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

//controls
/* SDL_KeyCode p1Controls = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT} */
/* SDL_KeyCode p2Controls = {SDLK_COMMA, SDLK_o, SDLK_a, SDLK_e} */

int main(int argc, char *argv[]) //required by SDL
{

  if (!initialiseSDL()) {
    printf("Failed to initialise\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      //main loop flag
      bool quit = false;

      //event handler

      _InputHandler::Instance()->init();
      /* input.handleKeyboardEvent(&e); */

      //object
      Dot dot;
      player p1(800);
      p1.keyConfig(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,SDL_SCANCODE_RIGHT);
      player p2(300);
      p2.keyConfig(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);

      //set the wall
      SDL_Rect wall;
      wall.x = 600;
      wall.y = 400;
      wall.w = 40;
      wall.h = 40;
      //text color
      SDL_Color textColor = {0,0,0,255};

      //while app is running
      while (!_InputHandler::Instance()->quit) {
        //handle input and events in the queue
        _InputHandler::Instance()->update();
        p1.move();
        p1.simulate();

        p2.move();
        p2.simulate();
        //clear screen
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        //render the wall
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderDrawRect(gRenderer, &wall);

        //render objects
        /* dot.render(); */
        p1.render();
        p2.render();

        //update screen
        SDL_RenderPresent(gRenderer);
      }

    }
  }

  killSDL();

  return 0;
}
