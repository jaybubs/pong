#pragma once
#include <Text.h>
#include <SDL.h>

class Score
{
public:
  Score ();
  virtual ~Score ();

  Text text;
  int score1 = 0;
  int score2 = 0;

  void display(SDL_Renderer* tRenderer);


private:
  /* data */
};
