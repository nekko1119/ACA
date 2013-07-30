#ifndef ACA_GAME_BOSS3_H
#define ACA_GAME_BOSS3_H

#include "Enemy.h"
#include "LazerList.h"
#include <map>
#include <vector>

namespace aca { namespace game {

class Boss3 : public Enemy
{
public:
    enum State
    {
        Stand,
        Run,
        Shoot1,	//溜め
        Shoot2,	//発射中
        Dead
    };

    Boss3();
    CollisionMap getWeaponCollision() const {return lazer.getCollision();}

private:
    static const float RunSpeed;	//走る速さ

    State curState;
    std::map<State, resource::Animation> state;//状態とアニメーション
    bool isTurn;	//向き
    VECTOR current;	//移動量
    bool isShoot;	//撃つモーションかどうか
    bool isShot;	//撃ったかどうか
    int index;	//アニメーションインデックス

    resource::DefaultImage lazerImage;	//レーザー画像
    std::vector<resource::Animation> lazerAnimation;
    std::vector<resource::Animation> lazerAnimation2;
    LazerList lazer;
};

}}

#endif