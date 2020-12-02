#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <Vector2D.h>

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2,
};

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

  std::vector<bool> mouseButtonStates;
  Vector2D* mPos;

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

  /* mouse shit */
  bool getMouseButtonState(int buttonNum)
  {
    return mouseButtonStates[buttonNum];
  }

  Vector2D* getMousePos()
  {
    return mPos;
  }

  void reset();

private:
  InputHandler() {};
  ~InputHandler() {};

  void keyDown(SDL_Event* event);
  void keyUp(SDL_Event* event);

  void onMouseMove(SDL_Event& e);
  void onMouseButtonDown(SDL_Event& e);
  void onMouseButtonUp(SDL_Event& e);
  

};

/* gives a unique call name for the InputHandler class to identify it as a singleton */
typedef InputHandler _InputHandler;
