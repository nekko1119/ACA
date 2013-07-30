#ifndef ACA_SCENE_TITLE_H
#define ACA_SCENE_TITLE_H

#include "MainScene.h"
#include "Image.hpp"

namespace aca { namespace scene {

class Title: public MainScene
{
public:
	Title();
	void update(Main* m);

private:
	void clamp(int& index);

	static const int MaxMenuNum = 2;	//メニューの数

	aca::resource::DefaultImage titleImage;
	aca::resource::DefaultImage no;	//非選択
	aca::resource::DefaultImage yes;	//選択
	int index;	//モード選択
};

}}

#endif