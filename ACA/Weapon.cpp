#include "Weapon.h"
#include "Collision.h"
#include "Fps.h"
#include "CollisionMap.h"
using namespace aca::game;

Weapon::Weapon
	(
	std::shared_ptr<Position> position,
	DynamicObject::Direction direction,
	VECTOR& speed,
	aca::resource::DefaultImage& image,
	aca::resource::Animation& animation,
	RECT rect
	)
	: DynamicObject(position, direction, rect ,image),
	speed(speed),
	animation(animation)
{
	position->add(this);
}

void Weapon::update()
{
	if(direction == DynamicObject::Right)
	{
		VAddFrame(position, speed);
	}
	else
	{
		VECTOR v = {-speed.x, -speed.y, -speed.z};
		VAddFrame(position, v);
	}

	subject->set(position);
	animation.update();
}

void Weapon::draw() const
{
	if(isDead)
	{
		return;
	}

	POINT p = {static_cast<int>(position.x), static_cast<int>(position.y)};
	image.draw(p, animation.getIndex(), direction == DynamicObject::Right);
}