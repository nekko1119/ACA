#ifndef ACA_SCENE_ENDING_H
#define ACA_SCENE_ENDING_H

#include "MainScene.h"
#include "Image.hpp"

namespace aca { namespace scene {

class Ending : public MainScene
{
public:
	Ending();
	~Ending();

	void update(Main* m);

private:
	float offset;
	aca::resource::DefaultImage image;
};

}}

#endif