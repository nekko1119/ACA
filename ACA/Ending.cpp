#include "Ending.h"
#include "Title.h"
#include "Main.h"
#include "Sound.h"
#include <DxLib.h>
using namespace aca::scene;

Ending::Ending() : offset(480.0f)
{
	image.load("files/image/ending.png");
	ChangeVolumeSoundMem(255 * 30 / 100, Sound::end);
	PlaySoundMem(Sound::end, DX_PLAYTYPE_LOOP);
}

Ending::~Ending()
{
	StopSoundMem(Sound::end);
}

void Ending::update(Main* m)
{
	if(offset == 0)
	{
		if(m->getInput().GetInstance(1)->GetButton(BUTTON_A).IsPush())
		{
			m->setNextScene(std::make_shared<Title>());
		}
	}
	else
	{
		if(m->getInput().GetInstance(1)->GetButton(BUTTON_UP).IsHitKey())
		{
			offset -= 3.0f;
		}
	}
	POINT p = {0, static_cast<int>(offset)};
	offset -= 0.1f;;
	if(offset < 0)
	{
		offset = 0;
	}
	image.draw(p);
}