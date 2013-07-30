#include "LazerList.h"
#include <algorithm>
using namespace aca::game;

LazerList::LazerList(aca::resource::DefaultImage& image, RECT rect) : rect(rect), collision(false), image(image)
{
}

void LazerList::push(aca::resource::Animation* animation, VECTOR position, DynamicObject::Direction direction)
{
    positions.push_back(std::make_shared<Position>(position));
    lazer.push_back(Lazer(positions.back(), direction, image, animation, rect));
    collision.add(&lazer.back());
}

void LazerList::update()
{
    for(auto it = lazer.begin(); it != lazer.end(); ++it)
    {
        printf("%d\n", it->getIsDead());
        it->update();
    }

    lazer.erase(std::remove_if(lazer.begin(), lazer.end(), [](Lazer l)->bool
    {
        return l.getIsFinished() || l.getIsDead();
    }), lazer.end());

    collision.update();
}

void LazerList::draw() const
{
    for(auto it = lazer.begin(); it != lazer.end(); ++it)
    {
        it->draw();
    }
}

bool LazerList::isFinished() const
{
    for(auto it = lazer.begin(); it != lazer.end(); ++it)
    {
        if(!(it->getIsFinished()))
        {
            return false;
        }
    }
    return true;
}

void LazerList::DeleteCollision()
{
    for(auto it = lazer.begin(); it != lazer.end(); ++it)
    {
        it->die();
    }
    collision.clear();
}