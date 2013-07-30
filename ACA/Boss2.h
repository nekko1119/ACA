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
    static const float RunSpeed;	//���鑬���ő�
    static const float JumpPower;
    static const float Gravity;

    State curState;
    std::map<State, resource::Animation> state;//��ԂƃA�j���[�V����
    bool isTurn;	//����
    VECTOR current;	//�ړ���
    int index;		//�A�j���[�V�����C���f�b�N�X
    resource::DefaultImage cry;//����
    float speed;
    bool isOn;	//�ڒn�t���O
    float accel;	//�����x
};

}}

#endif