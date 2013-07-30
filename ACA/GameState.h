#ifndef ACA_GAME_GAMESTATE_H
#define ACA_GAME_GAMESTATE_H

#include "Player.h"
#include "Enemy.h"
#include "Image.hpp"

namespace aca { namespace game {

class GameState
{
public:
    //Œã‚Åˆø”‘‚¦‚é‚æ
    GameState(std::string back, int stageID);

    void update();
    void draw() const;

    bool isDead() const;
    bool isClear() const;

private:
    Player player;
    std::shared_ptr<Enemy> enemy;
    resource::DefaultImage back;
};

}}

#endif