#ifndef ACA_SCENE_GAME_CLEAR_H
#define ACA_SCENE_GAME_CLEAR_H

#include "GameScene.h"
#include "Image.hpp"

namespace aca { namespace scene { namespace game {

class Clear : public GameScene
{
public:
    Clear();
    ~Clear();

    void update(Game* g);

private:
    resource::DefaultImage image;
    int count;
};

}}}

#endif