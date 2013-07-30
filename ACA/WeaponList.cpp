#include "WeaponList.h"
#include "Config.h"
#include <algorithm>
using namespace aca::game;

WeaponList::WeaponList(aca::resource::DefaultImage& image, aca::resource::Animation& animation, VECTOR speed, RECT rect)
    : image(image),
    animation(animation),
    speed(speed),
    rect(rect),
    collision(true)
{
}

void WeaponList::push(VECTOR position, DynamicObject::Direction direction)
{
    positions.push_back(std::make_shared<Position>(position));
    weapons.push_back(std::make_shared<Weapon>(Weapon(positions.back(), direction, speed, image, animation, rect)));
    collision.add(weapons.back().get());
}

void WeaponList::update()
{
    for(auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        (*it)->update();
    }	

    weapons.erase(std::remove_if(weapons.begin(), weapons.end(), [](std::shared_ptr<Weapon> w)->bool
    {
        RECT rect = w->getAbsRect();
        return (rect.right < 0 || rect.bottom < 0 || Config::WindowWidth < rect.left || Config::WindowHeight < rect.top);
    }), weapons.end());

    collision.update();
}

void WeaponList::draw() const
{
    for(auto it = weapons.begin(); it != weapons.end(); ++it)
    {
        (*it)->draw();
    }

    //debug
    //collision.draw();
}

int WeaponList::getSize() const
{
    return weapons.size();
}