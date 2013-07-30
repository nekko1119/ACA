#include "Main.h"
#include "Title.h"
#include "Fps.h"
#include "Config.h"
#include "resource.h"
#include "Sound.h"//音
#include <DxLib.h>
#include <stdexcept>
using namespace aca::scene;

//ヘッダで定義しちゃダメ
Controller* Controller::instance[DX_INPUT_PAD16];

Main::Main() : input(*Controller::GetInstance(1)), isExit(false)
{
	if(!initialize())
	{
		throw std::runtime_error("DXLibの初期化に失敗");
	}

	Sound();//音

	//メインシーンの最初はタイトル
	sceneState = std::make_shared<Title>();
}

Main::~Main()
{
	DxLib_End();
}

//メインシーンの実行
void Main::execute()
{
	while(ProcessMessage() == 0 && !isExit)
	{
		ClearDrawScreen();
		clsDx();

		input.Update();
		Fps::getInstance().update();

		sceneState->update(this);

		printfDx("fps : %.1f", Fps::getInstance().getFps());
		ScreenFlip();
	}
}

//次のシーンをセット
void Main::setNextScene(std::shared_ptr<MainScene> scene)
{
	sceneState = scene;
}

void Main::exit()
{
	isExit = true;
}

bool Main::initialize() const
{
	if(SetOutApplicationLogValidFlag(FALSE) == -1)			//ログ出力を行わない
		return false;
	if(ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)		//ウインドウモードで起動する
		return false;
	if(SetWindowIconID(IDI_ICON) == -1)						//アイコンを設定する
		return false;
	if(SetAlwaysRunFlag(FALSE) == -1)						//非アクティブ時には処理を止める
		return false;
	if(SetGraphMode(Config::WindowWidth, Config::WindowHeight, DEFAULT_COLOR_BITDEPTH) != DX_CHANGESCREEN_OK)//ウインドウのサイズを設定する
		return false;
	if(SetMainWindowText(Config::WindowTitle.c_str()) == -1)//タイトルを設定する
		return false;
	if(DxLib_Init() == -1)									//DXライブラリを初期化する
		return false;
	if(SetDrawArea(0, 0, Config::WindowWidth, Config::WindowHeight) == -1)//描画可能領域を設定する
		return false;
	if(SetDrawScreen(DX_SCREEN_BACK) == -1)					//裏描画に設定する
		return false;
	if(SetTransColor(255, 0, 255) == -1)					//透過色を設定する
		return false;
	if(SetMouseDispFlag(TRUE) == -1)						//画面にマウスポインタを表示する
		return false;
	if(SetFontSize(32) == -1)								//文字サイズを設定する
		return false;
	if(SetUseDXArchiveFlag(TRUE) == -1)						//DXアーカイブファイルを使うかどうか設定する
		return false;
	if(SetDxLibEndPostQuitMessageFlag(FALSE) == -1)			//DXライブラリ終了時にPostQuitMessageを呼ぶかどうかを設定する
		return false;

	//キー設定
	if(!input.LoadConfig(Config::KeyConfig.c_str(), "Player"))
	{
		input.SetButton(BUTTON_UP, KEY_INPUT_UP, PAD_INPUT_UP);
		input.SetButton(BUTTON_DOWN, KEY_INPUT_DOWN, PAD_INPUT_DOWN);
		input.SetButton(BUTTON_RIGHT, KEY_INPUT_RIGHT, PAD_INPUT_RIGHT);
		input.SetButton(BUTTON_LEFT, KEY_INPUT_LEFT, PAD_INPUT_LEFT);
		input.SetButton(BUTTON_A, KEY_INPUT_Z, PAD_INPUT_A);
		input.SetButton(BUTTON_B, KEY_INPUT_X, PAD_INPUT_B);
		input.SetButton(BUTTON_C, KEY_INPUT_C, PAD_INPUT_C);
		input.SetButton(BUTTON_START, KEY_INPUT_ESCAPE, PAD_INPUT_START);

		input.SaveConfig(Config::KeyConfig.c_str(), "Player");
	}

	return true;
}