#ifndef ACA_FPS_H
#define ACA_FPS_H

#include "Config.h"
#include <vector>
#include <DxLib.h>

namespace aca {

//Singletonパターン
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

	int time;		//1フレーム前の時間(ms)
	int count;		//何回時間を取得したか
	float frame;	//1フレームの時間(ms)
	std::vector<int> total;//取得した値を格納する配列
};

void VAddFrame(VECTOR& src, const VECTOR& diff);

}

#endif