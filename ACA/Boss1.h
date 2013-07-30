#ifndef ACA_GAME_BOSS1_H
#define ACA_GAME_BOSS1_H

#include "Enemy.h"
#include <map>

namespace aca { namespace game {

class Boss1 : public Enemy
{
public:
    enum State
    {
        Stand,
        Run,
        Shoot,
        Dead
    };

    Boss1();
    ~Boss1();

private:
    static const float RunSpeed;	//走る速さ

    State curState;
    std::map<State, resource::Animation> state;//状態とアニメーション
    bool isTurn;	//向き
    VECTOR current;	//移動量
    bool isShoot;	//撃つモーションかどうか
    bool isShot;	//撃ったかどうか
    int index;	//アニメーションインデックス
    int counter; //撃った時間
    bool isFirst;	//1発目を撃ったかどうか
};

}}

#endif