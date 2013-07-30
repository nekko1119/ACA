#ifndef ACA_GAME_IACTOR_H
#define ACA_GAME_IACTOR_H

#include "IObserver.h"
#include "Position.h"
#include "Image.hpp"

namespace aca { namespace game {

class DynamicObject : public IObserver
{
public:
    //����
    enum Direction
    {
        Right,	//�E
        Left	//��
    };

    DynamicObject(std::shared_ptr<Position> subject, Direction direction, RECT rect, resource::DefaultImage image);
    RECT getAbsRect() const;
    VECTOR getPosition() const;
    void die();
    bool getIsDead() const;
    void notify();

    virtual ~DynamicObject();

protected:
    std::shared_ptr<Position> subject;//�ώ@�Ώ�
    VECTOR position;		//���W
    RECT rect;				//���W����̑��ΏՓ˔���
    Direction direction;	//����
    bool isDead;			//�L���ȃf�[�^���ǂ���
    resource::DefaultImage image;//�摜
};

RECT makeRect(int leftupX, int leftupy, int rightdownX, int rightdownY);

}}

#endif