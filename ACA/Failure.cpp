#include "Failure.h"
#include "Game.h"
#include "Controller.hpp"
#include "Sound.h"
using namespace aca::scene::game;

static aca::resource::DefaultImage over;
Failure::Failure() : count(0)
{
    image.load(std::string("files/image/failure.png"));
    over.load("files/image/gameover.png");
    StopSoundMem(Sound::yuiBGM);
    StopSoundMem(Sound::china);
    StopSoundMem(Sound::kyoko);
}

void Failure::update(Game* g)
{
    auto state = g->getState();
    if(count > 360)
    {
        g->moveTo(Game::Title);
    }
    else if(count > 180)
    {
        POINT p = {0, 0};
        over.draw(p);
    }
    else
    {
        state->update();
        state->draw();

        POINT p = {0, 0};
        image.draw(p);
    }
    ++count;
}