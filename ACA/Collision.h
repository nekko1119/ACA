#ifndef ACA_GAME_COLLISION_H
#define ACA_GAME_COLLISION_H

#include "DynamicObject.h"

namespace aca { namespace game {

class Collision
{
public:
    ~Collision();//debug
    explicit Collision(DynamicObject* object);
    bool isHit(const Collision& rhs) const;
    void draw() const;
    bool isDead() const;
    void invisible();
    DynamicObject* get() const {return object;}

private:
    DynamicObject* object;
};

}}

#endif