#include "Ready.h"
#include "Game.h"
#include "Play.h"
using namespace aca::scene::game;

Ready::Ready() : hasLoad(false), count(0)
{
	image.push_back(resource::DefaultImage());
	image.push_back(resource::DefaultImage());
	image.push_back(resource::DefaultImage());

	image[0].load("files/image/ready1.png");
	image[1].load("files/image/ready2.png");
	image[2].load("files/image/ready3.png");
}

void Ready::update(Game* g)
{
	if(!hasLoad)
	{
		g->load();
		hasLoad = true;
	}

	g->getState()->draw();

	POINT p = {0, 0};
	if(count > 180)
	{
		g->setNextScene(std::make_shared<Play>());
	}
	else if(count > 120)
	{
		image[0].draw(p);
	}
	else if(count > 60)
	{
		image[1].draw(p);
	}
	else
	{
		image[2].draw(p);
	}

	++count;
}