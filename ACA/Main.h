#ifndef ACA_SCENE_MAIN_H
#define ACA_SCENE_MAIN_H

#include "Controller.hpp"
#include <memory>

namespace aca { namespace scene {

class IScene;
class MainScene;

//メインのシーケンス遷移クラス
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

	std::shared_ptr<MainScene> sceneState;	//メインのシーン。Stateパターンを使用
	Controller& input;						//仮想コントローラー
	bool isExit;	//終了フラグ
};

}}

#endif