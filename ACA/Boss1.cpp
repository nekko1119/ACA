#include "Boss1.h"
#include "Player.h"
#include "Fps.h"
#include "Sound.h"
using namespace aca::game;

const float Boss1::RunSpeed = 70.0f;

Boss1::Boss1()
    :
Enemy
    (
    TurnSelect(1),
    std::make_shared<Position>(VGet(Config::WindowWidth - 50.0f - 64.0f, Config::GroundLine, 0.0f)),
    resource::DefaultImage("files/image/yui.png", 49, resource::makePoint(7, 7), resource::makePoint(64, 64)),
    image,
    resource::Animation(8, 35, 2),
    VGet(100.0f, 0.0f, 0.0f),
    makeRect(28, 28, 20, 37)
    ),
    curState(Stand),
    isTurn(direction != Left),
    isShoot(false),
    isShot(false),
    index(0),
    counter(0),
    isFirst(false)
{
    state.insert(std::make_pair(Stand, resource::Animation(16, 0, 4)));
    state.insert(std::make_pair(Run, resource::Animation(8, 7, 6)));
    state.insert(std::make_pair(Shoot, resource::Animation(8, 28, 6)));
    state.insert(std::make_pair(Dead, resource::Animation(16, 42, 5)));

    subject->add(this);
    collision.add(this);

    PlaySoundMem(Sound::yuiBGM, DX_PLAYTYPE_LOOP);
    patterns.push_back([&](Player* player)
    {
        if(curState != Dead)
        {
            if(position.x < 1.0f)
            {
                position.x = 1.0f;
                direction = Right;
                if(!isShoot)
                {
                    curState = Shoot;
                }
            }
            if(Config::WindowWidth - 65.0f < position.x)
            {
                position.x = Config::WindowWidth - 65.0f;
                direction = Left;
                if(!isShoot)
                {
                    curState = Shoot;
                }
            }

            isTurn = direction == Right;

            if(curState == Shoot)
            {
                isShoot = true;
                if(!isShot)
                {
                    PlaySoundMem(Sound::yui, DX_PLAYTYPE_BACK);
                    weapons.push(position, direction);
                    isShot = true;
                    isFirst = true;
                    counter = GetNowCount();
                }
                else if(isFirst && GetNowCount() - counter > 500)
                {
                    state.at(curState).reset();
                    PlaySoundMem(Sound::yui, DX_PLAYTYPE_BACK);
                    weapons.push(position, direction);
                    isFirst = false;
                }
                else if(state.at(curState).getIsLoop())
                {
                    state.at(curState).reset();
                    curState = Run;
                }
            }
            else
            {
                isShoot = false;
                isShot = false;
                int d = isTurn ? 1 : -1;
                current = VGet(RunSpeed * d, 0.0f, 0.0f);

                if(fabs(current.x) < 0.01f)
                {
                    curState = Stand;
                }
                else
                {
                    curState = Run;
                }
            }

            VAddFrame(position, current);

            //debugコマンド
            if(CheckHitKey(KEY_INPUT_E))
            {
                life.reduce(50);
            }

            if(!isIncur && collision.check(player->getWeaponCollision()))
            {
                isIncur = true;
                life.reduce(5);
            }
            else if(isIncur)
            {
                ++count;
                if(count > Enemy::MatchlessTime)
                {
                    isIncur = false;
                    count = 0;
                }
            }

            if(life.isDead())
            {
                curState = Dead;
                StopSoundMem(Sound::yuiBGM);
            }
        }

        if(!state.at(Dead).getIsLoop())
        {
            state.at(curState).update();
            index = state.at(curState).getIndex();
        }
        else
        {
            index = 46;//死亡アニメーションの最後のインデックス
        }

        weapons.update();
        collision.update();
        current = VGet(0.0f, 0.0f, 0.0f);
    });

    draw_ = [&]()
    {
        printfDx("ボスの体力　：　%d\n", life.get());
        weapons.draw();

        if(isIncur && curState != Dead)
        {
            if(count % 4 < 2)
            {
                return;
            }
        }

        POINT p = {static_cast<int>(position.x), static_cast<int>(position.y)};

        image.draw(p, index, isTurn);

        //collision.draw();
    };
}

Boss1::~Boss1()
{
    StopSoundMem(Sound::yuiBGM);
}