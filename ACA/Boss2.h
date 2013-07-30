#ifndef ACA_GAME_BOSS2_H
#define ACA_GAME_BOSS2_H

#include "Enemy.h"
#include <map>

namespace aca { namespace game {

class Boss2 : public Enemy
{
public:
    enum State
    {
        Stand,
        Run,
        Dead
    };

    Boss2();
    ~Boss2();

private:
    static const float RunSpeed;	//走る速さ最大
    static const float JumpPower;
    static const float Gravity;

    State curState;
    std::map<State, resource::Animation> state;//状態とアニメーション
    bool isTurn;	//向き
    VECTOR current;	//移動量
    int index;		//アニメーションインデックス
    resource::DefaultImage cry;//泣く
    float speed;
    bool isOn;	//接地フラグ
    float accel;	//加速度
};

}}

#endif