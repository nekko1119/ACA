#include "Clear.h"
#include "Ready.h"
#include "Game.h"
#include "Clear.h"
#include "Sound.h"
using namespace aca::scene::game;

Clear::Clear() : count(0)
{
    image.load(std::string("files/image/win.png"));
    PlaySoundMem(Sound::win, DX_PLAYTYPE_BACK);
}
Clear::~Clear()
{
    StopSoundMem(Sound::win);
}

void Clear::update(Game* g)
{
    auto state = g->getState();

    if(count > 540)
    {
        if(g->hasClearAllStage())
        {
            g->moveTo(Game::Ending);
        }
        else
        {
            g->gotoNextStage();
            g->setNextScene(std::make_shared<Ready>());
        }
    }

    state->update();
    POINT p = {0, 0};
    state->draw();
    image.draw(p);
    ++count;
}