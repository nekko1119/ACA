#include "Main.h"
#include "Title.h"
#include "Fps.h"
#include "Config.h"
#include "resource.h"
#include "Sound.h"//��
#include <DxLib.h>
#include <stdexcept>
using namespace aca::scene;

//�w�b�_�Œ�`������_��
Controller* Controller::instance[DX_INPUT_PAD16];

Main::Main() : input(*Controller::GetInstance(1)), isExit(false)
{
	if(!initialize())
	{
		throw std::runtime_error("DXLib�̏������Ɏ��s");
	}

	Sound();//��

	//���C���V�[���̍ŏ��̓^�C�g��
	sceneState = std::make_shared<Title>();
}

Main::~Main()
{
	DxLib_End();
}

//���C���V�[���̎��s
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

//���̃V�[�����Z�b�g
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
	if(SetOutApplicationLogValidFlag(FALSE) == -1)			//���O�o�͂��s��Ȃ�
		return false;
	if(ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)		//�E�C���h�E���[�h�ŋN������
		return false;
	if(SetWindowIconID(IDI_ICON) == -1)						//�A�C�R����ݒ肷��
		return false;
	if(SetAlwaysRunFlag(FALSE) == -1)						//��A�N�e�B�u���ɂ͏������~�߂�
		return false;
	if(SetGraphMode(Config::WindowWidth, Config::WindowHeight, DEFAULT_COLOR_BITDEPTH) != DX_CHANGESCREEN_OK)//�E�C���h�E�̃T�C�Y��ݒ肷��
		return false;
	if(SetMainWindowText(Config::WindowTitle.c_str()) == -1)//�^�C�g����ݒ肷��
		return false;
	if(DxLib_Init() == -1)									//DX���C�u����������������
		return false;
	if(SetDrawArea(0, 0, Config::WindowWidth, Config::WindowHeight) == -1)//�`��\�̈��ݒ肷��
		return false;
	if(SetDrawScreen(DX_SCREEN_BACK) == -1)					//���`��ɐݒ肷��
		return false;
	if(SetTransColor(255, 0, 255) == -1)					//���ߐF��ݒ肷��
		return false;
	if(SetMouseDispFlag(TRUE) == -1)						//��ʂɃ}�E�X�|�C���^��\������
		return false;
	if(SetFontSize(32) == -1)								//�����T�C�Y��ݒ肷��
		return false;
	if(SetUseDXArchiveFlag(TRUE) == -1)						//DX�A�[�J�C�u�t�@�C�����g�����ǂ����ݒ肷��
		return false;
	if(SetDxLibEndPostQuitMessageFlag(FALSE) == -1)			//DX���C�u�����I������PostQuitMessage���ĂԂ��ǂ�����ݒ肷��
		return false;

	//�L�[�ݒ�
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