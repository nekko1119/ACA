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
    //������̏��
    enum State
    {
        Stand,	//����
        Run,	//����
        JumpUp,	//�W�����v�㏸
        JumpDown,//�W�����v���~
        Shoot,	//�U��
        Dead1,	//���S(�O���A�j���[�V����)
        Dead2,	//���S(�㔼���[�v�A�j���[�V����)
        Invisible,//����
        Win		//����
    };

    explicit Player(std::shared_ptr<Position> position);

    void update(Enemy* enemy);	//�\������摜�̍X�V�ƍ��W�̍X�V
    void move(State state, Direction direction, int frame = 0);//�ړ�����
    void draw() const;	//�`��
    void setDirection(Direction d);//�����̐ݒ�
    CollisionMap getWeaponCollision() const {return weaponList.getCollision();}

    bool isDead() const {return life.isDead();}

private:
    static const float RunSpeed;	//���鑁��
    static const float JumpSpeed[2];//�W�����v�̍���
    static const float Gravity;		//�d��
    static const int MaxBulletNum = 3;//�����ɑ��݂ł���e�̐�
    static const int InvisibleTime = 1000;//�A�b�J���[���̎���

    VECTOR inertia;				//�����x�N�g��
    std::map<State, resource::Animation> state;//��ԂƃA�j���[�V����
    State curState;				//���݂̃X�e�[�g
    bool isTurn;				//�E:true ��:false
    bool isShot;				//�e�𔭎˂��郂�[�V���������Ă��邩�ǂ���
    bool isFinished;			//����̒e�����������ǂ���
    bool isInvisible;			//�������ǂ���
    bool isOn;					//�ڒn���Ă��邩�ǂ���
    bool isIncur;				//��e�������ǂ���
    int count;					//��e���Ă���̌o�߃t���[��
    WeaponList weaponList;		//�e
    CollisionMap collision;		//���@�̔���
    Life life;					//�̗�
    int index;					//�A�j���[�V�����C���f�b�N�X
    int offset;					//�A�b�J���[�����̉摜�\���p�̂���
    int invisibleCount;			//�����ł����鎞��
};

}}

#endif