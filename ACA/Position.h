#ifndef ACA_GAME_POSITION_H
#define ACA_GAME_POSITION_H

#include "IObserver.h"
#include <DxLib.h>
#include <list>

namespace aca { namespace game {

class Position : public aca::ISubject
{
public:
	explicit Position(VECTOR position);

	void add(IObserver* observer);
	VECTOR get() const;
	void set(VECTOR position);

private:
	std::list<IObserver*> observerList;
	VECTOR position;	//ç¿ïW
};

}}

#endif