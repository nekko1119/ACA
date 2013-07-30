#ifndef ACA_GAME_WEAPONLIST_H
#define ACA_GAME_WEAPONLIST_H

#include "Weapon.h"
#include "Image.hpp"
#include "Animation.h"
#include "CollisionMap.h"
#include <list>
#include <memory>

namespace aca { namespace game {

class WeaponList
{
public:
    WeaponList(resource::DefaultImage& image, resource::Animation& animation, VECTOR speed, RECT rect);

    void push(VECTOR position, DynamicObject::Direction direction);
    void update();
    void draw() const;
    int getSize() const;
    CollisionMap getCollision() const {return collision;}

private:
    resource::DefaultImage image;
    resource::Animation animation;
    VECTOR speed;
    RECT rect;
    std::list<std::shared_ptr<Position>> positions;
    std::list<std::shared_ptr<Weapon>> weapons;
    CollisionMap collision;
};

}}

#endif