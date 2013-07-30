#ifndef ACA_GAME_LAZERLIST_H
#define ACA_GAME_LAZERLIST_H

#include "Lazer.h"
#include "CollisionMap.h"

namespace aca { namespace game {

class LazerList
{
public:
    LazerList(aca::resource::DefaultImage& image, RECT rect);

    void push(aca::resource::Animation* animation, VECTOR position, DynamicObject::Direction direction);
    void update();
    void draw() const;
    bool isFinished() const;
    CollisionMap getCollision() const {return collision;}
    void DeleteCollision();

private:
    RECT rect;
    std::list<std::shared_ptr<Position>> positions;
    std::list<Lazer> lazer;
    aca::resource::DefaultImage& image;
    CollisionMap collision;
};

}}

#endif