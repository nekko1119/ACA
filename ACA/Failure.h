#ifndef ACA_SCENE_GAME_FAILURE_H
#define ACA_SCENE_GAME_FAILURE_H

#include "GameScene.h"
#include "Image.hpp"

namespace aca { namespace scene { namespace game {

class Failure : public GameScene
{
public:
    Failure();

    void update(Game* g);

private:
    resource::DefaultImage image;
    int count;
};

}}}

#endif