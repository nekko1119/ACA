#include "Game.h"
#include "Play.h"
#include "Animation.h"
#include "Controller.hpp"
#include "CollisionMap.h"
#include "Failure.h"
#include "Clear.h"
#include <DxLib.h>
using namespace aca::scene::game;

void Play::update(Game* g)
{
	auto state = g->getState();

	state->update();
	state->draw();

	bool isDead = state->isDead();
	bool isClear = state->isClear();

	if(isDead)
	{
		g->setNextScene(std::make_shared<Failure>());
	}
	else if(isClear)
	{
		//g->gotoNextStage();
		g->setNextScene(std::make_shared<Clear>());
	}
}