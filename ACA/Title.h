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

	static const int MaxMenuNum = 2;	//���j���[�̐�

	aca::resource::DefaultImage titleImage;
	aca::resource::DefaultImage no;	//��I��
	aca::resource::DefaultImage yes;	//�I��
	int index;	//���[�h�I��
};

}}

#endif