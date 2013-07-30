#ifndef ACA_GAME_ENEMY_H
#define ACA_GAME_ENEMY_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "DynamicObject.h"
#include "CollisionMap.h"
#include "WeaponList.h"
#include "Config.h"
#include "Life.h"
#include <functional>
#include <vector>

namespace aca { namespace game {

class Player;

struct TurnSelect
{
    TurnSelect(int max) : count(0), max(max)
    {
    }

    int operator()()
    {
        if(count >= max)
        {
            count = 0;
        }
        return count++;
    }
private:
    int count;
    int max;
};

class Enemy : public DynamicObject
{
public:
    Enemy(std::function<int ()> select, std::shared_ptr<Position> position, resource::DefaultImage image, resource::DefaultImage& weaponImage,
        resource::Animation animation, VECTOR speed, RECT rect);

    void update(Player* player);
    void draw() const;
    CollisionMap getCollision() const {return collision;}
    bool Dead() const;
    virtual CollisionMap getWeaponCollision() const {return weapons.getCollision();}

protected:
    static const int MatchlessTime;
    std::function<int ()> select;	//���̃p�^�[���̑I�ѕ�
    std::vector<std::function<void (Player*)>> patterns;//�U���p�^�[��
    std::function<void ()> draw_;	//�`��
    CollisionMap collision;//����
    int next;		//���̃p�^�[���ԍ�
    bool isFinished;//���̃p�^�[�����I��������ǂ���
    bool isIncur;	//��e���Ă��邩�ǂ���
    int count;		//��e���Ă���̌o�߃t���[��
    Life life;
    WeaponList weapons;//�e
};

}}

#endif