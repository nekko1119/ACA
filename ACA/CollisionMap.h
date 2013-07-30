#ifndef ACA_GAME_COLLISIONMAP_H
#define ACA_GAME_COLLISIONMAP_H

#include "Collision.h"
#include <map>
#include <string>

namespace aca { namespace game {

class CollisionMap
{
public:
    explicit CollisionMap(bool isDeletable);

    void add(DynamicObject* obj);
    void remove(DynamicObject* obj);
    void clear();
    bool check(CollisionMap& rhs);
    void update();
    int getSize() const;
    void draw() const;

private:
    std::list<Collision> collisions;
    bool isDeletable;
};

}} 

#endif