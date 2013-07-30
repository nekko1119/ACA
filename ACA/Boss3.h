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
        Shoot1,	//����
        Shoot2,	//���˒�
        Dead
    };

    Boss3();
    CollisionMap getWeaponCollision() const {return lazer.getCollision();}

private:
    static const float RunSpeed;	//���鑬��

    State curState;
    std::map<State, resource::Animation> state;//��ԂƃA�j���[�V����
    bool isTurn;	//����
    VECTOR current;	//�ړ���
    bool isShoot;	//�����[�V�������ǂ���
    bool isShot;	//���������ǂ���
    int index;	//�A�j���[�V�����C���f�b�N�X

    resource::DefaultImage lazerImage;	//���[�U�[�摜
    std::vector<resource::Animation> lazerAnimation;
    std::vector<resource::Animation> lazerAnimation2;
    LazerList lazer;
};

}}

#endif