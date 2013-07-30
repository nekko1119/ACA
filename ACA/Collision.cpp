#include "Collision.h"
#include "Config.h"
#include <DxLib.h>
using namespace aca::game;

Collision::Collision(DynamicObject* object) : object(object)
{
}

Collision::~Collision()
{
}

bool Collision::isHit(const Collision& rhs) const
{
    RECT l = object->getAbsRect();
    RECT r = rhs.object->getAbsRect();

    return r.left <= l.right && l.left <= r.right && l.top <= r.bottom && r.top <= l.bottom;
}

void Collision::draw() const
{
    RECT r = object->getAbsRect();
    DrawBox
        (
        r.left,
        r.top,
        r.right,
        r.bottom,
        GetColor(255, 0, 0),
        false
        );
}

bool Collision::isDead() const
{
    RECT rect = object->getAbsRect();
    return object->getIsDead() || (rect.right < 0 || rect.bottom < 0 || Config::WindowWidth < rect.left || Config::WindowHeight < rect.top);
}

void Collision::invisible()
{
    object->die();
}