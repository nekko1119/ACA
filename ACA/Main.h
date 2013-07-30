#ifndef ACA_SCENE_MAIN_H
#define ACA_SCENE_MAIN_H

#include "Controller.hpp"
#include <memory>

namespace aca { namespace scene {

class IScene;
class MainScene;

//���C���̃V�[�P���X�J�ڃN���X
class Main
{
public:
	Main();
	~Main();

	void execute();
	void setNextScene(std::shared_ptr<MainScene> scene);
	const Controller& getInput() const {return input;}
	void exit();

private:
	bool initialize() const;

	std::shared_ptr<MainScene> sceneState;	//���C���̃V�[���BState�p�^�[�����g�p
	Controller& input;						//���z�R���g���[���[
	bool isExit;	//�I���t���O
};

}}

#endif