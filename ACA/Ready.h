#ifndef ACA_SCENE_GAME_READY_H
#define ACA_SCENE_GAME_READY_H

#include "GameScene.h"
#include "Image.hpp"

namespace aca { namespace scene { namespace game {

class Ready : public GameScene
{
public:
	Ready();

	void update(Game* g);

private:
	bool hasLoad;
	int count;
	std::vector<resource::DefaultImage> image;
};

}}}

#endif