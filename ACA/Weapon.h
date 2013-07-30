#ifndef ACA_GAME_WEAPON_H
#define ACA_GAME_WEAPON_H

#include "Image.hpp"
#include "DynamicObject.h"
#include "Animation.h"
#include <DxLib.h>

namespace aca { namespace game {

//�e
class Weapon : public DynamicObject
{
public:
    Weapon(
        std::shared_ptr<Position> position,
        DynamicObject::Direction direction,
        VECTOR& speed,
        resource::DefaultImage& image,
        resource::Animation& animation,
        RECT rect
        );

    virtual ~Weapon(){}

    virtual void update();
    void draw() const;

private:
    VECTOR speed;			//����
    resource::Animation animation;//�A�j���[�V����
};

}}

#endif