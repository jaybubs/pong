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

  Texture gDotTexture;
  Score score;
}

void Dot::move()
{
  float dt = 0.01667;
  mposx += mvelx * dt;
  mposy += mvely * dt;

  if (mposx < 0){
  mposx = utils::screenW*0.5;
  mposy = utils::screenH*0.5;
  mvelx *= -1;
  mvely = 0;
  score.score1++;
  std::cout << score.score1 << std::endl;
  } else if (mposx + DOT_WIDTH > utils::screenW) {
  mposx = utils::screenW*0.5;
  mposy = utils::screenH*0.5;
  mvelx *= -1;
  mvely = 0;
  score.score2++;
  std::cout << score.score2 << std::endl;
  }

  if ((mposy < 0) || (mposy + DOT_HEIGHT > utils::screenH)) {
    mvely *= -1;
  }
}

void Dot::render(SDL_Renderer* gRenderer)
{
  gDotTexture.render(mposx, mposy, gRenderer);
}

/* static textures need be loaded only once so use otuside the main game loop */
bool Dot::loadMedia(SDL_Renderer* gRenderer)
{
  bool success = true;

  gDotTexture.loadFromFile("dot.png", gRenderer);
  /* gPlayerTexture.loadFromFile("cry.png"); */
  SDL_Color textColor = {0,0,0,255};
  //no need to rerender a static texture every time so load once

  return success;
}
