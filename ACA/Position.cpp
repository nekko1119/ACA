#include "Position.h"
using namespace aca::game;

Position::Position(VECTOR position) : position(position)
{
}

void Position::add(aca::IObserver* observer)
{
	observerList.push_back(observer);
}

VECTOR Position::get() const
{
	return position;
}

void Position::set(VECTOR position)
{
	this->position = position;

	for(auto it = observerList.begin(); it != observerList.end(); ++it)
	{
		//(*it)->notify();
	}
}