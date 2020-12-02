#pragma once

/* unconstructable class for scoping purposes */
class physics
{
public:
  physics() = delete;

  dt = 0.1667f;
  void suvat(float *pos, float *vel, float *acc)
  {
    *acc -= *vel * 10.f;
    *pos = *pos + *vel * dt + *acc * dt * dt * 0.5f;
    *vel = *vel + *acc * dt;
  }
};


void suvat(float 
{
  /* suvat but vectors */
  /*   a = vt */
  /*   s = s0 + vt + at^2/2 */
  /*   v = v0 + at */

  Vector2D accV(accx, accy);
  Vector2D velV(velx, vely);
  Vector2D posV(posx, posy);

  float delta = 0.016666667f;
  accV -= velV * 10.f;
  posV += velV * delta + accV * delta * delta * 0.5f;
  velV += accV * delta;

}
