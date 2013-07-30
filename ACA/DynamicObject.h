#ifndef ACA_GAME_IACTOR_H
#define ACA_GAME_IACTOR_H

#include "IObserver.h"
#include "Position.h"
#include "Image.hpp"

namespace aca { namespace game {

class DynamicObject : public IObserver
{
public:
    //向き
    enum Direction
    {
        Right,	//右
        Left	//左
    };

    DynamicObject(std::shared_ptr<Position> subject, Direction direction, RECT rect, resource::DefaultImage image);
    RECT getAbsRect() const;
    VECTOR getPosition() const;
    void die();
    bool getIsDead() const;
    void notify();

    virtual ~DynamicObject();

protected:
    std::shared_ptr<Position> subject;//観察対象
    VECTOR position;		//座標
    RECT rect;				//座標からの相対衝突判定
    Direction direction;	//向き
    bool isDead;			//有効なデータかどうか
    resource::DefaultImage image;//画像
};

RECT makeRect(int leftupX, int leftupy, int rightdownX, int rightdownY);

}}

#endif