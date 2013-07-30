#include "Player.h"
#include "Enemy.h"
#include "Fps.h"
#include "Config.h"
#include "Controller.hpp"
#include "Sound.h"//音
using namespace aca::game;

const float Player::RunSpeed = 60.0f;
const float Player::JumpSpeed[2] = {160.0f, 70.0f};
const float Player::Gravity = 180.0f;

static bool isClear = false;
Player::Player(std::shared_ptr<Position> position)
    : DynamicObject(position, Right, makeRect(23, 7, 40, 64), resource::DefaultImage("files/image/akari.png", 77, resource::makePoint(7, 11), resource::makePoint(64, 64))),
    inertia(VGet(0.0f, 0.0f, 0.0f)),
    curState(Stand),
    isTurn(true),
    isShot(false),
    isFinished(false),
    isOn(true),
    isInvisible(false),
    isIncur(false),
    count(0),
    weaponList(image, resource::Animation(8, 28, 6), VGet(100.0f, 0.0f, 0.0f), makeRect(26, 26, 46, 38)),
    collision(false),
    life(Config::PlayerLife),
    index(0),
    offset(0),
    invisibleCount(InvisibleTime)//5秒//回復速度が消費の2分の1なので、3倍の300frame( = 5秒) * 2 = 600frameにしている
{
    state.insert(std::make_pair(Stand, resource::Animation(16, 0, 4)));
    state.insert(std::make_pair(Run, resource::Animation(8, 7, 6)));
    state.insert(std::make_pair(JumpUp, resource::Animation(1, 14, 1)));
    state.insert(std::make_pair(JumpDown, resource::Animation(1, 16, 1)));
    state.insert(std::make_pair(Shoot, resource::Animation(4, 21, 6)));
    state.insert(std::make_pair(Dead1, resource::Animation(16, 56, 7)));
    state.insert(std::make_pair(Dead2, resource::Animation(8, 63, 2)));
    state.insert(std::make_pair(Win, resource::Animation(16, 70, 3)));

    position->add(this);
    collision.add(this);
    isClear = false;
}

static bool canJump = false;
static VECTOR current = {0.0f, 0.0f, 0.0f};
void Player::move(State state, Direction direction, int frame)
{
    if(curState == Dead1 || curState == Dead2 || isClear)
    {
        return;
    }

    if(state == Invisible && invisibleCount > 0)
    {
        if(isInvisible)
        {
            PlaySoundMem(Sound::n, DX_PLAYTYPE_BACK);
            isInvisible = false;
        }
        else
        {
            PlaySoundMem(Sound::a, DX_PLAYTYPE_BACK);
            isInvisible = true;
        }
    }

    if(state == Stand)
    {
        inertia.x = 0.0f;
        if(inertia.y < -40.0f)
        {
            inertia.y = -40.0f;
        }
    }
    else if(state == Shoot && !isInvisible && weaponList.getSize() < MaxBulletNum)
    {
        this->state.at(Shoot).reset();
        isShot = true;
        isFinished = false;
    }
    else if(state == Run)
    {
        if(curState == Stand || curState == Run)
        {
            if(direction == Right)
            {
                current = VAdd(current, VGet(RunSpeed, 0.0f, 0.0f));
            }
            else
            {
                current = VAdd(current, VGet(-RunSpeed, 0.0f, 0.0f));
            }
        }
        else if(curState == JumpUp || curState == JumpDown)
        {
            if(direction == Right)
            {
                inertia.x = RunSpeed;
            }
            else
            {
                inertia.x = -RunSpeed;
            }
        }
    }
    else if(state == JumpUp || state == JumpDown)
    {
        if(1 <= frame && frame <= 6 && !canJump)
        {
            PlaySoundMem(Sound::jump, DX_PLAYTYPE_BACK);
            if(frame % 5 == 1)
            {
                current = VAdd(current, VGet(0.0f, -JumpSpeed[frame / 5], 0.0f));
            }
            isOn = false;
        }

        inertia = VAdd(inertia, current);
    }
}

void Player::update(Enemy* enemy)
{
    offset = isInvisible ? 35 : 0;

    //空中にいてジャンプボタンを離した時がある
    if(!isOn && Controller::GetInstance(1)->GetButton(BUTTON_A).IsRelease())
    {
        canJump = true;
    }

    if(position.y >= Config::GroundLine)
    {
        inertia = current;
        if(fabs(current.x) < 0.01f)
        {
            if(!life.isDead())
            {
                curState = Stand;
            }
        }
        else
        {
            curState = Run;
            isTurn = current.x >= 0.0f;
        }
        isOn = true;
        canJump = false;
    }
    else
    {
        VAddFrame(inertia, VGet(0.0f, Gravity, 0.0f));
        curState = inertia.y < 0 ? JumpUp : JumpDown;
    }

    if(life.isDead())
    {
        if(curState != Dead1 && curState != Dead2)
        {
            curState = Dead1;
        }
        else if(state.at(curState).getIsLoop())
        {
            curState = Dead2;
        }
    }
    else if(enemy->Dead())
    {
        curState = Win;
        isClear = true;
    }

    VAddFrame(position, inertia);
    if(position.x < 0.0f)
    {
        position.x = 0.0f;
    }
    if(Config::WindowWidth - 48.0f < position.x)
    {
        position.x = Config::WindowWidth - 48.0f;
    }

    subject->set(position);

    if(position.y > Config::GroundLine)
    {
        position.y = Config::GroundLine;
    }
    direction = isTurn ? DynamicObject::Right : DynamicObject::Left;

    if(!state.at(Win).getIsLoop())
    {
        state.at(curState).update();
        index = state.at(curState).getIndex();
    }
    else
    {
        index = 72;
    }

    //弾の処理
    if(isShot)
    {
        if(!isFinished)
        {
            PlaySoundMem(Sound::attack, DX_PLAYTYPE_BACK);
            weaponList.push(VGet(position.x, position.y - 8.0f, position.z), this->direction);
            isFinished = true;
        }
        if(state.at(Shoot).getIsLoop())
        {
            isShot = false;
        }
    }
    state.at(Shoot).update();

    //被弾
    if(!isInvisible && collision.check(enemy->getCollision()) && !isIncur)
    {
        PlaySoundMem(Sound::damage, DX_PLAYTYPE_BACK);
        isIncur = true;
        life.reduce(6);
    }
    else if(isIncur)
    {
        ++count;
        if(count > 120)
        {
            isIncur = false;
            count = 0;
        }
    }
    if(!isInvisible && collision.check(enemy->getWeaponCollision()) && !isIncur)
    {
        isIncur = true;
        life.reduce(4);
    }
    else if(isIncur)
    {
        ++count;
        if(count > 120)
        {
            isIncur = false;
            count = 0;
        }
    }

    if(isInvisible)
    {
        if(invisibleCount < 0)
        {
            isInvisible = false;
            invisibleCount = 0;
        }
        else
        {
            invisibleCount -= 3;
        }
    }
    else
    {
        ++invisibleCount;
        if(invisibleCount > InvisibleTime)
        {
            invisibleCount = InvisibleTime;
        }
    }
    current = VGet(0.0f, 0.0f, 0.0f);
    weaponList.update();
    collision.update();

    //debugコマンド
    if(CheckHitKey(KEY_INPUT_W))
    {
        life.reduce(24);
    }
}

void Player::draw() const
{
    int l = life.get();
    if(l < 0)
    {
        l = 0;
    }
    printfDx("あかりの体力　：　%d\n", l);
    printfDx("あっかりーん　：　%d\n", invisibleCount / 10);
    if(isIncur && !(curState == Dead1 || curState == Dead2) && curState != Win)
    {
        if(count % 4 < 2)
        {
            return;
        }
    }

    POINT p = {static_cast<int>(position.x), static_cast<int>(position.y)};
    if(isShot)
    {
        image.draw(p, state.at(Shoot).getIndex(), isTurn);
    }
    else
    {
        if(curState != Dead1 && curState != Dead2 && !isClear)
        {
            image.draw(p, index + offset, isTurn);
        }
        else
        {
            image.draw(p, index, isTurn);
        }
    }

    weaponList.draw();
    //debug
    //collision.draw();
}

void Player::setDirection(Direction d)
{
    isTurn = d != Left;
}