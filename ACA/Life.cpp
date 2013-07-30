#include "Life.h"
using namespace aca::game;

Life::Life(int life) : life(life)
{
}

void Life::reduce(int damege)
{
    life -= damege;
}

bool Life::isDead() const
{
    return life <= 0;
}