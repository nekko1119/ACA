#include "DynamicObject.h"
using namespace aca::game;

DynamicObject::DynamicObject(std::shared_ptr<Position> subject, Direction direction, RECT rect,	aca::resource::DefaultImage image)
    :
subject(subject),
    position(subject->get()),
    direction(direction),
    rect(rect),
    isDead(false),
    image(image)
{
}

DynamicObject::~DynamicObject()
{
}

VECTOR DynamicObject::getPosition() const
{
    return position;
}

RECT DynamicObject::getAbsRect() const
{
    VECTOR p = position;
    RECT ret;
    int pivot = image.getX() / 2;
    POINT pt = {pivot - rect.left, pivot - rect.right};
    if(direction == Left)
    {
        ret = makeRect
            (
            static_cast<int>(p.x) + pivot - pt.x,
            static_cast<int>(p.y) + rect.top,
            static_cast<int>(p.x) + pivot - pt.y,
            static_cast<int>(p.y) + rect.bottom
            );
    }
    else
    {
        ret = makeRect
            (
            static_cast<int>(p.x) + pivot + pt.y,
            static_cast<int>(p.y) + rect.top,
            static_cast<int>(p.x) + pivot + pt.x,
            static_cast<int>(p.y) + rect.bottom
            );
    }

    return ret;
}

void DynamicObject::die()
{
    isDead = true;
}

bool DynamicObject::getIsDead() const
{
    return isDead;
}

void DynamicObject::notify()
{
    position = subject->get();
}

RECT aca::game::makeRect(int leftupX, int leftupy, int rightdownX, int rightdownY)
{
    RECT r = {leftupX, leftupy, rightdownX, rightdownY};
    return r;
}