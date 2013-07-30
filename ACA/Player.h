#ifndef ACA_GAME_PLAYER_H
#define ACA_GAME_PLAYER_H

#include "Animation.h"
#include "WeaponList.h"
#include "CollisionMap.h"
#include "Life.h"
#include <list>
#include <map>
#include <DxLib.h>

namespace aca { namespace game {

class Enemy;

class Player : public DynamicObject
{
public:
    //あかりの状態
    enum State
    {
        Stand,	//立ち
        Run,	//走り
        JumpUp,	//ジャンプ上昇
        JumpDown,//ジャンプ下降
        Shoot,	//攻撃
        Dead1,	//死亡(前半アニメーション)
        Dead2,	//死亡(後半ループアニメーション)
        Invisible,//透明
        Win		//勝利
    };

    explicit Player(std::shared_ptr<Position> position);

    void update(Enemy* enemy);	//表示する画像の更新と座標の更新
    void move(State state, Direction direction, int frame = 0);//移動処理
    void draw() const;	//描画
    void setDirection(Direction d);//向きの設定
    CollisionMap getWeaponCollision() const {return weaponList.getCollision();}

    bool isDead() const {return life.isDead();}

private:
    static const float RunSpeed;	//走る早さ
    static const float JumpSpeed[2];//ジャンプの高さ
    static const float Gravity;		//重力
    static const int MaxBulletNum = 3;//同時に存在できる弾の数
    static const int InvisibleTime = 1000;//アッカリーンの時間

    VECTOR inertia;				//慣性ベクトル
    std::map<State, resource::Animation> state;//状態とアニメーション
    State curState;				//現在のステート
    bool isTurn;				//右:true 左:false
    bool isShot;				//弾を発射するモーションをしているかどうか
    bool isFinished;			//今回の弾を撃ったかどうか
    bool isInvisible;			//透明かどうか
    bool isOn;					//接地しているかどうか
    bool isIncur;				//被弾したかどうか
    int count;					//被弾してからの経過フレーム
    WeaponList weaponList;		//弾
    CollisionMap collision;		//自機の判定
    Life life;					//体力
    int index;					//アニメーションインデックス
    int offset;					//アッカリーン中の画像表示用のずれ
    int invisibleCount;			//透明でいられる時間
};

}}

#endif