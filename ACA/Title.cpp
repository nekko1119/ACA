#include "Title.h"
#include "Main.h"
#include "Game.h"
#include "Config.h"
#include "Sound.h"
using namespace aca::scene;

Title::Title() : index(0)
{
	titleImage.load("files/image/title.png");
	yes.load("files/image/yes.png", 2, resource::makePoint(1, 2), resource::makePoint(196, 48));
	no.load("files/image/no.png", 2, resource::makePoint(1, 2), resource::makePoint(196, 48));
}

void Title::update(Main* m)
{	
	titleImage.draw(resource::makePoint(0, 0));
	int width = (Config::WindowWidth - yes.getX()) / 2;

	yes.draw(resource::makePoint(width, 380), index == 0 ? 0 : 1);
	no.draw(resource::makePoint(width, 428), index == 1 ? 0 : 1);

	if(m->getInput().GetButton(BUTTON_A).IsPush())
	{
		switch(index)
		{
		case 0:
			{
				m->setNextScene(std::make_shared<game::Game>());
				break;
			}
		case 1:
			{
				m->exit();
				break;
			}
		default:
			{
				MessageBox(nullptr, _T("‚¦‚Á"), _T("‚¦‚Á"), MB_OK);
				m->exit();
				break;
			}
		}
	}
	if(m->getInput().GetButton(BUTTON_DOWN).IsPush())
	{
		PlaySoundMem(Sound::title, DX_PLAYTYPE_BACK);
		++index;
		clamp(index);
	}
	if(m->getInput().GetButton(BUTTON_UP).IsPush())
	{
		PlaySoundMem(Sound::title, DX_PLAYTYPE_BACK);
		--index;
		clamp(index);
	}
}

void Title::clamp(int& index)
{
	if(index < 0)
	{
		index = MaxMenuNum - 1;
	}
	if(MaxMenuNum - 1 < index)
	{
		index = 0;
	}
}