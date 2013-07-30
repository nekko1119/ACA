#ifndef ACA_GAME_ENEMY_H
#define ACA_GAME_ENEMY_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "DynamicObject.h"
#include "CollisionMap.h"
#include "WeaponList.h"
#include "Config.h"
#include "Life.h"
#include <functional>
#include <vector>

namespace aca { namespace game {

class Player;

struct TurnSelect
{
    TurnSelect(int max) : count(0), max(max)
    {
    }

    int operator()()
    {
        if(count >= max)
        {
            count = 0;
        }
        return count++;
    }
private:
    int count;
    int max;
};

class Enemy : public DynamicObject
{
public:
    Enemy(std::function<int ()> select, std::shared_ptr<Position> position, resource::DefaultImage image, resource::DefaultImage& weaponImage,
        resource::Animation animation, VECTOR speed, RECT rect);

    void update(Player* player);
    void draw() const;
    CollisionMap getCollision() const {return collision;}
    bool Dead() const;
    virtual CollisionMap getWeaponCollision() const {return weapons.getCollision();}

protected:
    static const int MatchlessTime;
    std::function<int ()> select;	//次のパターンの選び方
    std::vector<std::function<void (Player*)>> patterns;//攻撃パターン
    std::function<void ()> draw_;	//描画
    CollisionMap collision;//判定
    int next;		//次のパターン番号
    bool isFinished;//今のパターンが終わったかどうか
    bool isIncur;	//被弾しているかどうか
    int count;		//被弾してからの経過フレーム
    Life life;
    WeaponList weapons;//弾
};

}}

#endif