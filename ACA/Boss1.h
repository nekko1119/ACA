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
    static const float RunSpeed;	//���鑬��

    State curState;
    std::map<State, resource::Animation> state;//��ԂƃA�j���[�V����
    bool isTurn;	//����
    VECTOR current;	//�ړ���
    bool isShoot;	//�����[�V�������ǂ���
    bool isShot;	//���������ǂ���
    int index;	//�A�j���[�V�����C���f�b�N�X
    int counter; //����������
    bool isFirst;	//1���ڂ����������ǂ���
};

}}

#endif