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
}

/* for now use a fixed list, figure out a solution later */
void player::keyConfig(SDL_Scancode upKey, SDL_Scancode downKey, SDL_Scancode leftKey, SDL_Scancode rightKey)
{
  up = upKey;
  down = downKey;
  left = leftKey;
  right = rightKey;
}

void player::move()
{
  accx = 0.f;
  accy = 0.f;
  if (keyPressed(left)) {
      accx -= 2000;
  }
  if (keyPressed(right)) {
      accx += 2000;
  }
  if (keyPressed(up)) {
      accy -= 2000;
  }
  if (keyPressed(down)) {
      accy += 2000;
  }
}

void player::simulate()
{
  //suvat
  float delta = 0.016667f;
  accx -= velx * 5.f;
  posx += velx * delta + accx * delta * delta * 0.5f;
  velx += accx * delta;

  accy -= vely * 100.f;
  posy += vely * delta + accy * delta * delta * 0.5f;
  vely += accy * delta;
  if (vely != 0) {
      std::cout << "pos: " << posy << std::endl;
      std::cout << "vel: " << vely << std::endl;
      std::cout << "acc: " << accy << std::endl;
  }
}


/* 1. player.acc = 0 */
/* 2. button press down should change the player.acc value */
/* 3. button release should reset player.acc back to 0 */
/* 4. the rest of the player variables pos and vel should be controlled by phsyics.suvat */
/* 5. a change in player.acc will trigger a recalculation of player.vel and player.pos based on physics.suvat */
/* 6. check for collisions and reset acc pos vel accordingly */
