#include "Fps.h"
#include <boost/foreach.hpp>
#include <DxLib.h>
using namespace aca;

Fps& Fps::getInstance()
{
	static Fps instance;
	return instance;
}

Fps::Fps() : time(GetNowCount()), count(0), frame(0.0f), total(Config::MaxFpsCount)
{
}

float Fps::getFps() const
{
	if(frame != 0.0f)
	{
		return 1000.0f / frame;
	}
	else
	{
		return 60.0f;
	}
}

float Fps::getFrameTime() const
{
	if(frame != 0.0f && frame < 32.0f)
	{
		return frame;
	}
	else
	{
		return 16.666f;
	}
}

void Fps::update()
{
	total[count] = GetNowCount() - time;
	time = GetNowCount();

	if(static_cast<unsigned int>(count) < total.size() - 1)
	{
		++count;
	}
	else
	{
		frame = 0.0f;
		BOOST_FOREACH(int it, total)
		{
			frame += it;
		}
		frame /= Config::MaxFpsCount;
		count = 0;		
	}
}

void aca::VAddFrame(VECTOR& src, const VECTOR& diff)
{
	src.x += static_cast<int>(diff.x / aca::Fps::getInstance().getFrameTime());
	src.y += static_cast<int>(diff.y / aca::Fps::getInstance().getFrameTime());
	src.z += static_cast<int>(diff.z / aca::Fps::getInstance().getFrameTime());
}