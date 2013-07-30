#ifndef ACA_FPS_H
#define ACA_FPS_H

#include "Config.h"
#include <vector>
#include <DxLib.h>

namespace aca {

//Singleton�p�^�[��
class Fps
{
public:
	static Fps& getInstance();

	void update();
	float getFps() const;
	float getFrameTime() const;

private:
	Fps();
	Fps(const Fps& rhs);
	Fps& operator=(const Fps& rhs);

	int time;		//1�t���[���O�̎���(ms)
	int count;		//���񎞊Ԃ��擾������
	float frame;	//1�t���[���̎���(ms)
	std::vector<int> total;//�擾�����l���i�[����z��
};

void VAddFrame(VECTOR& src, const VECTOR& diff);

}

#endif