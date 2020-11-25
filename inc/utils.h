#pragma once

struct utils {
  static const int screenW = 1280;
  static const int screenH = 960;

  static bool checkCollision(SDL_Rect a, SDL_Rect b)
  {
    //sides of rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //calc the sides
    leftA = a.x;
    rightA = a.x+a.w;
    topA = a.y;
    bottomA = a.y+a.h;
    leftB = b.x;
    rightB = b.x+b.w;
    topB = b.y;
    bottomB = b.y+b.h;

    //if any of the sides from A are outside of B
    if (bottomA <= topB) {
      return false;
    }
    if (topA >= bottomB) {
      return false;
    }
    if (rightA <= leftB) {
      return false;
    }
    if (leftA >= rightB) {
      return false;
    }
    //if none are outside mark as colliding
    return true;
  }
};
