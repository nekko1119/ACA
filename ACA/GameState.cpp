#include "GameState.h"
#include "Config.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Controller.hpp"
using namespace aca::game;

GameState::GameState(std::string back, int stageID)
    :
player(std::make_shared<Position>(VGet(50.0f, Config::GroundLine, 0.0f)))
{
    switch(stageID)
    {
    case 1:
        enemy = std::make_shared<Boss1>();
        break;
    case 2:
        enemy = std::make_shared<Boss2>();
        break;
    case 3:
        enemy = std::make_shared<Boss3>();
        break;
    default:
        break;
    }
    this->back.load(back);
}

void GameState::update()
{
    if(GetJoypadInputState(DX_INPUT_KEY_PAD1))
    {
        static bool isPushed = false;
        if(!isPushed && Controller::GetInstance(1)->GetButton(BUTTON_RIGHT).IsHitKey())
        {
            player.move(aca::game::Player::Run, aca::game::DynamicObject::Right);
            player.setDirection(aca::game::DynamicObject::Right);
            isPushed = true;
        }
        else
        {
            isPushed = false;
        }

        if(!isPushed && Controller::GetInstance(1)->GetButton(BUTTON_LEFT).IsHitKey())
        {
            player.move(aca::game::Player::Run, aca::game::DynamicObject::Left);
            player.setDirection(aca::game::DynamicObject::Left);
            isPushed = true;
        }
        else
        {
            isPushed = false;
        }
    }
    //‰½‚à‰Ÿ‚µ‚Ä‚È‚¢
    else
    {
        player.move(aca::game::Player::Stand, aca::game::DynamicObject::Left);
    }


    if(Controller::GetInstance(1)->GetButton(BUTTON_A).IsHitKey())
    {
        player.move(aca::game::Player::JumpUp, aca::game::DynamicObject::Left, Controller::GetInstance(1)->GetButton(BUTTON_A).GetPushCount());
    }

    if(Controller::GetInstance(1)->GetButton(BUTTON_B).IsPush())
    {
        player.move(aca::game::Player::Shoot, aca::game::DynamicObject::Left);
    }
    if(Controller::GetInstance(1)->GetButton(BUTTON_C).IsPush())
    {
        player.move(aca::game::Player::Invisible, aca::game::DynamicObject::Left);
    }

    player.update(enemy.get());
    enemy->update(&player);
}

void GameState::draw() const
{
    POINT p = {0, 0};
    back.draw(p);
    enemy->draw();
    player.draw();
}

bool GameState::isDead() const
{
    return player.isDead();
}

bool GameState::isClear() const
{
    return enemy->Dead();
}