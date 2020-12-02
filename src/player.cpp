#pragma once
#include <iostream>
#include <player.h>

template<typename SDL_Scancode>
bool keyPressed(SDL_Scancode a)
{
  return _InputHandler::Instance()->keyPressed(a);
}

player::player()
{
  posx = 0;
  posy = utils::screenH/2 - this->playerHeight/2;
  velx = 0;
  vely = 0;
  accx = 0;
  accy = 0;

  /* instantiate entity */
  /* have the entity weild the width and height properties for collion purposes */
}

/* for now use a fixed list, figure out a solution later */
void player::keyConfig(SDL_Scancode upKey, SDL_Scancode downKey)
{
  up = upKey;
  down = downKey;
}

  int i = 0;
void player::move()
{
  accx = 0.f;
  accy = 0.f;
  if (keyPressed(up)) {
      accy -= 20000;
  }
  if (keyPressed(down)) {
      accy += 20000;
  }
  if (_InputHandler::Instance()->getMouseButtonState(LEFT)) {
    /* accvec.dir = mPos - playerPos */
    /* accvec.mag += 5000; */
    std::cout << _InputHandler::Instance()->getMousePos() << std::endl;
    }

}

void player::arenaCollision()
{
  if (posy < 0) {
    posy = 0;
    vely *= 0;
  }
  if (posy + playerHeight > utils::screenH) {
    posy = utils::screenH - playerHeight;
    vely *=0;
  }
  
}

void player::simulate()
{
  //suvat
  float delta = 0.016666667f;
  accx -= velx * 10.f;
  posx += velx * delta + accx * delta * delta * 0.5f;
  velx += accx * delta;

  accy -= vely * 10.f;
  posy += vely * delta + accy * delta * delta * 0.5f;
  vely += accy * delta;

  arenaCollision();
}


/* 1. player.acc = 0 */
/* 2. button press down should change the player.acc value */
/* 3. button release should reset player.acc back to 0 */
/* 4. the rest of the player variables pos and vel should be controlled by phsyics.suvat */
/* 5. a change in player.acc will trigger a recalculation of player.vel and player.pos based on physics.suvat */
/* 6. check for collisions and reset acc pos vel accordingly */
