#pragma once


struct Collision {
  /* use when position is given by the centre of box and its halfwidths */
  bool halfaabbaabb(
      float p1x, float p1y, 
      float hs1x, float hs1y, 
      float p2x, float p2y, 
      float hs2x, float hs2y
      )
  {
    return  (p1x + hs1x > p2x - hs2x &&
        p1x - hs1x < p2x + hs2x &&
        p1y + hs1y > p2y - hs2y &&
        p1y + hs1y < p2y + hs2y);

  }
  /* use when position is given by the topleft corner and its full witdhs */
  bool aabbaabb(
      float p1x, float p1y, 
      float w1x, float h1y, 
      float p2x, float p2y, 
      float w2x, float h2y
      )
  {
    return  (p1x + w1x > p2x &&
        p1x < p2x + w2x &&
        p1y + h1y > p2y &&
        p1y < p2y + h2y);

  }
};
