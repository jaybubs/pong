#pragma once

/* class player a; */
/* class player b; */

struct utils {
  static const int screenW = 1280;
  static const int screenH = 960;


  /* static bool checkCollision(player a, player b) */
  /* { */

  /*   //sides of rectangles */
  /*   int leftA, leftB; */
  /*   int rightA, rightB; */
  /*   int topA, topB; */
  /*   int bottomA, bottomB; */

  /*   //calc the sides */
  /*   leftA = a.posx; */
  /*   rightA = a.posx+a.playerWidth; */
  /*   topA = a.posy; */
  /*   bottomA = a.posy+a.playerHeight; */
  /*   leftB = b.posx; */
  /*   rightB = b.posx+b.playerWidth; */
  /*   topB = b.posy; */
  /*   bottomB = b.posy+b.playerHeight; */

  /*   //if any of the sides from A are outside of B */
  /*   if (bottomA <= topB) { */
  /*     return false; */
  /*   } */
  /*   if (topA >= bottomB) { */
  /*     return false; */
  /*   } */
  /*   if (rightA <= leftB) { */
  /*     return false; */
  /*   } */
  /*   if (leftA >= rightB) { */
  /*     return false; */
  /*   } */
  /*   //if none are outside mark as colliding */
  /*   return true; */
  /* } */
};
