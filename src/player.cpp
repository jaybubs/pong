#pragma once
#include <iostream>
#include <player.h>

template<typename SDL_Scancode>
bool keyPressed(SDL_Scancode a)
{
  return _InputHandler::Instance()->keyPressed(a);
}

player::player(int x)
{
  posx = x;
  posy = utils::screenH/2 - this->height/2;
  velx = 0;
  vely = 0;
  accx = 0;
  accy = 0;
  mCollider.w = this->width;
  mCollider.h = this->height;
  float acc = 2000;

}

/* for now use a fixed list, figure out a solution later */
void player::keyConfig(SDL_KeyCode upKey, SDL_KeyCode downKey, SDL_KeyCode leftKey, SDL_KeyCode rightKey)
{
  up = upKey;
  down = downKey;
  left = leftKey;
  right = rightKey;
}

void player::move()
{
  if (keyPressed(SDL_SCANCODE_LEFT)) {
      std::cout << accx << std::endl;
      accx -= 2000;
  }
  if (keyPressed(SDL_SCANCODE_RIGHT)) {
    std::cout << "you are right" << std::endl;
      accx += 2000;
  }
}

void player::simulate()
{
  //suvat
  float delta = 0.016667f;
  accx -= velx * 10.f;
  velx += accx * delta;
  posx = posx + velx * delta + accx * delta * delta * 0.5f;
  /* velx = velx + accx *delta ; */
}


/* 1. player.acc = 0 */
/* 2. button press down should change the player.acc value */
/* 3. button release should reset player.acc back to 0 */
/* 4. the rest of the player variables pos and vel should be controlled by phsyics.suvat */
/* 5. a change in player.acc will trigger a recalculation of player.vel and player.pos based on physics.suvat */
/* 6. check for collisions and reset acc pos vel accordingly */
