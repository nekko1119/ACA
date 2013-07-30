#ifndef ACA_CONFIG_H
#define ACA_CONFIG_H

#include <string>

namespace aca {

struct Config
{
	static const int WindowWidth;			//�E�C���h�E�̕�
	static const int WindowHeight;			//�E�C���h�E�̍���
	static const std::string WindowTitle;	//�E�C���h�E�̃^�C�g��

	static const std::string KeyConfig;		//�L�[�R���t�B�O�̃t�@�C����
	static const int MaxFpsCount;			//Fps������v���������ς���邩�̉���v�����邩

	static const float GroundLine;			//�n��̍���

	static const int PlayerLife;			//�v���C���[�̗̑͏����l
};

}

#endif