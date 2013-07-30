#include "Boss3.h"
#include "Player.h"
#include "Fps.h"
#include "Sound.h"
using namespace aca::game;

const float Boss3::RunSpeed = 70.0f;

Boss3::Boss3()
    :
Enemy
    (
    TurnSelect(1),
    std::make_shared<Position>(VGet(Config::WindowWidth - 50.0f - 64.0f, Config::GroundLine, 0.0f)),
    resource::DefaultImage("files/image/kyoko.png", 56, resource::makePoint(7, 8), resource::makePoint(64, 64)),
    //京子は通常の弾は使わないのでダミーデータを入れる
    //ダミーデータここから
    image,
    resource::Animation(1, 1, 1),
    VGet(0.0f, 0.0f, 0.0f),
    makeRect(1, 1, 1, 1)
    //ダミーデータここまで
    ),
    curState(Stand),
    isTurn(direction != Left),
    isShoot(false),
    isShot(false),
    index(0),
    lazerImage(aca::resource::DefaultImage("files/image/lazer.png", 15, resource::makePoint(3, 5), resource::makePoint(128, 80))),
    lazer(LazerList(lazerImage, makeRect(0, 32, 128, 46)))
{

    state.insert(std::make_pair(Stand, resource::Animation(16, 0, 4)));
    state.insert(std::make_pair(Run, resource::Animation(8, 42, 6)));
    state.insert(std::make_pair(Shoot1, resource::Animation(3, 7, 29)));
    state.insert(std::make_pair(Shoot2, resource::Animation(4, 36, 4)));
    state.insert(std::make_pair(Dead, resource::Animation(16, 49, 1)));

    subject->add(this);
    collision.add(this);

    lazerAnimation.push_back(aca::resource::Animation(8, 0, 3));
    lazerAnimation.push_back(aca::resource::Animation(8, 3, 2));
    lazerAnimation.push_back(aca::resource::Animation(8, 6, 3));

    lazerAnimation2.push_back(aca::resource::Animation(8, 9, 3));
    lazerAnimation2.push_back(aca::resource::Animation(8, 9, 2));
    lazerAnimation2.push_back(aca::resource::Animation(8, 12, 3));

    PlaySoundMem(Sound::kyoko, DX_PLAYTYPE_LOOP);
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
                    curState = Shoot1;
                }
            }
            if(Config::WindowWidth - 65.0f < position.x)
            {
                position.x = Config::WindowWidth - 65.0f;
                direction = Left;
                if(!isShoot)
                {
                    curState = Shoot1;
                }
            }

            isTurn = (direction == Right);

            if(curState == Shoot1)
            {
                if(state.at(curState).getIsLoop())
                {
                    state.at(curState).reset();
                    curState = Shoot2;
                }
            }
            else if(curState == Shoot2)
            {
                PlaySoundMem(Sound::lazer, DX_PLAYTYPE_BACK);
                isShoot = true;
                if(!isShot)
                {
                    VECTOR v[5];
                    for(int i = 0; i < 5; ++i)
                    {
                        if(direction == Right)
                        {
                            v[i] = VGet(position.x + (64.0f + 128.0f * i), position.y, position.z);
                        }
                        else
                        {
                            v[i] = VGet(position.x - (128.0f + 128.0f * i), position.y, position.z);
                        }

                        if(i == 0)
                        {
                            lazer.push(lazerAnimation.data(), v[i], direction);
                        }
                        else
                        {
                            lazer.push(lazerAnimation2.data(), v[i], direction);
                        }
                    }
                    isShot = true;
                }
                if(lazer.isFinished())
                {
                    lazer.DeleteCollision();
                    StopSoundMem(Sound::lazer);
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
                StopSoundMem(Sound::kyoko);
            }
        }

        lazer.update();
        state.at(curState).update();
        index = state.at(curState).getIndex();
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
        lazer.draw();

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
            p.y = static_cast<int>(position.y) + 32;
        }
        image.draw(p, index, isTurn);
        //collision.draw();
    };
}