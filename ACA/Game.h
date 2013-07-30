#ifndef ACA_SCENE_GAME_GAME_H
#define ACS_SCENE_GAME_GAME_H

#include "MainScene.h"
#include "GameState.h"
#include <memory>

namespace aca { namespace scene { namespace game {

class GameScene;

class Game : public MainScene
{
public:
	//ã‚ÌŠK‘w‚Ö”ò‚Ô—p
	enum Scene
	{
		Title,
		Ending,

		None
	};

	Game();

	void update(aca::scene::Main* m);
	void setNextScene(std::shared_ptr<GameScene> scene);
	void moveTo(Scene scene);
	std::shared_ptr<aca::game::GameState> getState() const { return gameState; }
	void gotoNextStage();
	void load();
	bool hasClearAllStage() const {return stageID >= MaxStageNum;}

private:
	void moveScene(aca::scene::Main* m);

	static const int MaxStageNum = 3;

	int stageID;
	std::shared_ptr<GameScene> sceneState;	//ƒQ[ƒ€‚ÌƒV[ƒ“
	std::shared_ptr<aca::game::GameState> gameState;//ƒQ[ƒ€–{‘Ì
	Scene next;
};

}}}

#endif