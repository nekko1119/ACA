#include "Game.h"
#include "Play.h"
#include "Ready.h"
#include "Main.h"
#include "Title.h"
#include "Ending.h"
using namespace aca::scene::game;

Game::Game()
	:
stageID(1),
	next(None)
{
	sceneState = std::make_shared<Ready>();
}

void Game::update(aca::scene::Main* m)
{
	sceneState->update(this);
	moveScene(m);
}


void Game::setNextScene(std::shared_ptr<GameScene> scene)
{
	sceneState = scene;
}

void Game::moveTo(Scene scene)
{
	if(scene == None)
	{
		throw std::invalid_argument("Scene::None‚ª“n‚³‚ê‚Ü‚µ‚½");
	}
	next = scene;
}

void Game::moveScene(aca::scene::Main* m)
{
	switch(next)
	{
	case Title:
		m->setNextScene(std::make_shared<scene::Title>());
		break;
	
	case Ending:
		m->setNextScene(std::make_shared<scene::Ending>());
		break;
	}
	next = None;
}

void Game::gotoNextStage()
{
	++stageID;
}

void Game::load()
{
	switch(stageID)
	{
	case 1:
		gameState = std::make_shared<aca::game::GameState>(std::string("files/image/back1.png"), stageID);
		break;
	case 2:
		gameState = std::make_shared<aca::game::GameState>(std::string("files/image/back2.png"), stageID);
		break;
	case 3:
		gameState = std::make_shared<aca::game::GameState>(std::string("files/image/back3.png"), stageID);
		break;
	default:
		break;
	}
}