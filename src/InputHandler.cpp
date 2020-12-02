#include <InputHandler.h>

/* makes InputHandler a usable singleton */
InputHandler* InputHandler::instance = 0;

void InputHandler::init()
{
  for (int i = 0; i < 3; i++) {
    mouseButtonStates.push_back(false);
  }

  mPos = new Vector2D(0,0);
  
}

void InputHandler::update()
{
  /* must be here so the state can be reset and checked every iteration, not just initalise once and done */
  state = SDL_GetKeyboardState(0);

  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        keyDown(&event);
        break;
      case SDL_KEYUP:
        keyUp(&event);
        break;
      default:
        break;
    }
  }
}

void InputHandler::clean()
{
  
}


void InputHandler::onMouseButtonDown(SDL_Event& e)
{
  if (e.button.button == SDL_BUTTON_LEFT) {
      mouseButtonStates[LEFT] = true;
  }
  if (e.button.button == SDL_BUTTON_MIDDLE) {
      mouseButtonStates[MIDDLE] = true;
  }
  if (e.button.button == SDL_BUTTON_RIGHT) {
      mouseButtonStates[RIGHT] = true;
  }
}

void InputHandler::onMouseButtonUp(SDL_Event& e)
{
  if (e.button.button == SDL_BUTTON_LEFT) {
      mouseButtonStates[LEFT] = false;
  }
  if (e.button.button == SDL_BUTTON_MIDDLE) {
      mouseButtonStates[MIDDLE] = false;
  }
  if (e.button.button == SDL_BUTTON_RIGHT) {
      mouseButtonStates[RIGHT] = false;
  }
}

void InputHandler::onMouseMove(SDL_Event& e)
{
  mPos->setX(e.motion.x);
  mPos->setY(e.motion.y);
}

void InputHandler::reset()
{
  for (int i = 0; i < mouseButtonStates.size(); i++) {
    mouseButtonStates[i] = false;
  }
}

bool InputHandler::keyPressed(SDL_Scancode key)
{
  if (state != 0) {
     if (state[key] == 1) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

void InputHandler::keyDown(SDL_Event* event)
{

}
void InputHandler::keyUp(SDL_Event* event)
{

}

