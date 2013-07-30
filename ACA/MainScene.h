#ifndef ACA_SCENE_MAINSCENE_H
#define ACA_SCENE_MAINSCENE_H

namespace aca { namespace scene {

class Main;

class MainScene
{
public:
	~MainScene(){}

	virtual void update(Main* m) = 0;
};

}}

#endif