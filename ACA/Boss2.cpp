#include "Boss2.h"
#include "Player.h"
#include "Fps.h"
#include "Sound.h"
using namespace aca::game;

const float Boss2::RunSpeed = 160.0f;
const float Boss2::Gravity = 6.0f;
const float Boss2::JumpPower = 140.0f;

Boss2::Boss2()
    :
Enemy
    (
    TurnSelect(1),
    std::make_shared<Position>(VGet(Config::WindowWidth - 50.0f - 64.0f, Config::GroundLine, 0.0f)),
    resource::DefaultImage("files/image/chinatsu.png", 49, resource::makePoint(7, 7), resource::makePoint(64, 64)),
    image,
    resource::Animation(8, 35, 2),
    VGet(100.0f, 0.0f, 0.0f),
    makeRect(28, 28, 40, 37)
    ),
    curState(Stand),
    isTurn(direction != Left),
    current(VGet(0.0f, 0.0f, 0.0f)),
    index(0),
    speed(40.0f),
    isOn(true),
    accel(0.0f),
    cry("files/image/chinatsu_cry.png", 2, resource::makePoint(2, 1), resource::makePoint(96, 48))
{
    state.insert(std::make_pair(Stand, resource::Animation(16, 0, 4)));
    state.insert(std::make_pair(Run, resource::Animation(8, 7, 6)));
    state.insert(std::make_pair(Dead, resource::Animation(16, 0, 2)));

    subject->add(this);
    collision.add(this);

    PlaySoundMem(Sound::china, DX_PLAYTYPE_LOOP);
    patterns.push_back([&](Player* player)
    {
        if(curState != Dead)
        {
            if(position.x < 1.0f)
            {
                position.x = 1.0f;
                direction = Right;
            }
            if(Config::WindowWidth - 65.0f < position.x)
            {
                position.x = Config::WindowWidth - 65.0f;
                direction = Left;
                speed += 20;
            }
            if(speed > RunSpeed)
            {
                speed = RunSpeed;
            }

            isTurn = direction == Right;
            if(isOn)
            {
                accel = -JumpPower;
                isOn = false;
            }
            else
            {
                accel += Gravity;
            }
            int d = isTurn ? 1 : -1;
            current = VAdd(VGet(speed * d, accel, 0.0f), current);

            if(fabs(current.x) < 0.01f)
            {
                curState = Stand;
            }
            else
            {
                curState = Run;
            }

            VAddFrame(position, current);
            if(position.y > Config::GroundLine)
            {
                position.y = Config::GroundLine;
                accel = 0.0f;
                isOn = true;
            }
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
                StopSoundMem(Sound::china);
            }
        }
        state.at(curState).update();
        index = state.at(curState).getIndex();

        weapons.update();
        collision.update();
        current = VGet(0.0f, 0.0f, 0.0f);
    });

    draw_ = [&]()
    {
        int l = life.get();
        if(l < 0)
        {
            l = 0;
        }
        printfDx("ボスの体力　：　%d\n", l);
        weapons.draw();

        if(isIncur && curState != Dead)
        {
            if(count % 4 < 2)
            {
                return;
            }
        }

        POINT p;
        if(curState != Dead)
        {
            p.x = static_cast<int>(position.x);
            p.y = static_cast<int>(position.y);
        }
        else
        {
            p.x = static_cast<int>(position.x);
            p.y = static_cast<int>(position.y) + 16;
        }
        if(curState != Dead)
        {
            image.draw(p, index, isTurn);
        }
        else
        {
            cry.draw(p, index, isTurn);
        }

        //collision.draw();
    };
}

Boss2::~Boss2()
{
    StopSoundMem(Sound::china);
}