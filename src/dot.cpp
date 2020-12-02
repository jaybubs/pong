#pragma once
#include <dot.h>
#include <utils.h>

Dot::Dot()
{
  mposx = utils::screenW*0.5;
  mposy = utils::screenH*0.5;
  mvelx = 500;
  mvely = 0;
  mCollider.w = DOT_WIDTH;
  mCollider.h = DOT_HEIGHT;

}

void Dot::move()
{
  float dt = 0.01667;
  mposx += mvelx * dt;

  if ((mposx < 0) || (mposx + DOT_WIDTH > utils::screenW)) {
    mvelx *= -1;
  }

  mposy += mvely * dt;

  if ((mposy < 0) || (mposy + DOT_HEIGHT > utils::screenH)) {
    mvely *= -1;
  }
}
