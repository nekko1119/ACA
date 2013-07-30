#include "CollisionMap.h"
#include <algorithm>
using namespace aca::game;

CollisionMap::CollisionMap(bool isDeletable) : isDeletable(isDeletable)
{
}

void CollisionMap::add(DynamicObject* obj)
{
    collisions.push_back(Collision(obj));
}

void CollisionMap::remove(DynamicObject* obj)
{
    collisions.erase(std::remove_if(collisions.begin(), collisions.end(), [&obj](Collision& c)->bool
    {
        return c.get() == obj;
    }), collisions.end());
}

void CollisionMap::clear()
{
    collisions.erase(std::remove_if(collisions.begin(), collisions.end(), [](Collision& c)->bool
    {
        return true;
    }), collisions.end());
}

bool CollisionMap::check(CollisionMap& rhs)
{
    for(auto lit = collisions.begin(); lit != collisions.end(); ++lit)
    {
        for(auto rit = rhs.collisions.begin(); rit != rhs.collisions.end(); ++rit)
        {
            if(lit->isHit(*rit))
            {
                if(isDeletable)
                {
                    lit->invisible();
                    collisions.erase(lit);
                }
                if(rhs.isDeletable)
                {
                    rit->invisible();
                    rhs.collisions.erase(rit);
                }
                return true;
            }
        }
    }
    return false;
}

void CollisionMap::update()
{
    collisions.remove_if([](Collision& c)
    {
        return c.isDead();
    });
}

int CollisionMap::getSize() const
{
    return collisions.size();
}

void CollisionMap::draw() const
{
    for(auto it = collisions.begin(); it != collisions.end(); ++it)
    {
        it->draw();
    }
}