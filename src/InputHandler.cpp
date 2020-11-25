#include <InputHandler.h>

/* makes InputHandler a usable singleton */
InputHandler* InputHandler::instance = 0;

void InputHandler::init()
{
  
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


/* InputHandler::InputHandler():state(0) */
/* { */
/*   bool quit = false; */
/* }; */


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

