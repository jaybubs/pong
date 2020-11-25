#pragma once
#include <SDL.h>
#include <iostream>

/* this class is a singleton, so constructor is private */
class InputHandler
{
/*properties*/
public:
  /* to be referred to in the main while loop as while(!input.quit).... */
  bool quit;

private:
  const Uint8* state;
  static InputHandler* instance;

/*methods*/
public:
  /* calling to this function will return the only allowed existing instance or create a new one if not existing yet */
  static InputHandler* Instance()
  {
    if (instance == 0) {
      instance = new InputHandler();
    }
    return instance;
  }

  void init();
  void update();
  void clean();

  /* for key state mapping */
  bool keyPressed(SDL_Scancode key);

private:
  InputHandler() {};
  ~InputHandler() {};

  void keyDown(SDL_Event* event);
  void keyUp(SDL_Event* event);
  

};

/* gives a unique call name for the InputHandler class to identify it as a singleton */
typedef InputHandler _InputHandler;
