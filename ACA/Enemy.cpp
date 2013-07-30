#include "Enemy.h"
#include "Player.h"
using namespace aca::game;

const int Enemy::MatchlessTime = 50;
Enemy::Enemy(std::function<int ()> select, std::shared_ptr<Position> position, aca::resource::DefaultImage image, aca::resource::DefaultImage& weaponImage,
    aca::resource::Animation animation, VECTOR speed, RECT rect)
    :
DynamicObject(position, Left, makeRect(10, -5, 54, 69), image),
    collision(false),
    next(0),
    isFinished(false),
    isIncur(false),
    count(0),
    life(50),
    weapons(WeaponList(weaponImage, animation, speed, rect))
{
}

void Enemy::update(Player* player)
{
    if(isFinished)
    {
        next = select();
    }
    patterns.at(next)(player);
}

void Enemy::draw() const
{
    draw_();
}

bool Enemy::Dead() const
{
    return life.isDead();
}