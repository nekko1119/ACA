#ifndef ACA_CONFIG_H
#define ACA_CONFIG_H

#include <string>

namespace aca {

struct Config
{
	static const int WindowWidth;			//ウインドウの幅
	static const int WindowHeight;			//ウインドウの高さ
	static const std::string WindowTitle;	//ウインドウのタイトル

	static const std::string KeyConfig;		//キーコンフィグのファイル名
	static const int MaxFpsCount;			//Fpsが何回計測した平均を取るかの何回計測するか

	static const float GroundLine;			//地上の高さ

	static const int PlayerLife;			//プレイヤーの体力初期値
};

}

#endif