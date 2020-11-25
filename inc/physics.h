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
