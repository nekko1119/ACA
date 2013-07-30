#include "Lazer.h"
using namespace aca::game;

const int Lazer::Length = 60;

Lazer::Lazer
    (
    std::shared_ptr<Position> position,
    Direction direction,
    aca::resource::DefaultImage image,
    aca::resource::Animation* animation,
    RECT rect
    )
    :
DynamicObject(position, direction, rect, image),
    curState(Begin),
    isFinished(false),
    count(0)
{
    state.insert(std::make_pair(Begin, animation[0]));
    state.insert(std::make_pair(Now, animation[1]));
    state.insert(std::make_pair(End, animation[2]));

    position->add(this);
}

void Lazer::update()
{
    switch(curState)
    {
    case Begin:
        {
            if(state.at(curState).getIsLoop())
            {
                curState = Now;
            }
            break;
        }
    case Now:
        {
            ++count;
            if(count >= Length)
            {
                curState = End;
            }
            break;
        }
    case End:
        {
            if(state.at(curState).getIsLoop())
            {
                isFinished = true;
                break;
            }
        }
    }

    subject->set(position);
    state.at(curState).update();
}

void Lazer::draw() const
{
    POINT p = {static_cast<int>(position.x), static_cast<int>(position.y)};
    if(!state.at(End).getIsLoop())
    {
        image.draw(p, state.at(curState).getIndex(), direction == Left);
    }
}