#ifndef ACA_SCENE_GAME_GAMESCENE_H
#define ACA_SCENE_GAME_GAMESCENE_H

namespace aca { namespace scene { namespace game {

class Game;

class GameScene
{
public:
	~GameScene(){}

	virtual void update(Game* g) = 0;
};

}}}

#endif