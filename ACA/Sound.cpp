#include "Sound.h"

int Sound::a;
int Sound::n;
int Sound::attack;
int Sound::jump;
int Sound::damage;
int Sound::title;
int Sound::lazer;
int Sound::yui;
int Sound::yuiBGM;
int Sound::end;
int Sound::win;
int Sound::china;
int Sound::kyoko;

Sound::Sound()
{
	a = LoadSoundMem("files/sound/a.wav");
	n = LoadSoundMem("files/sound/n.wav");
	attack = LoadSoundMem("files/sound/attack.mp3");
	jump = LoadSoundMem("files/sound/jump.mp3");
	damage = LoadSoundMem("files/sound/damage.wav");
	title = LoadSoundMem("files/sound/title.mp3");
	lazer = LoadSoundMem("files/sound/lazer.wav");
	yui = LoadSoundMem("files/sound/BR.wav");
	yuiBGM = LoadSoundMem("files/sound/yuiBGM.wav");
	end = LoadSoundMem("files/sound/end.mp3");
	win = LoadSoundMem("files/sound/win.ogg");
	china = LoadSoundMem("files/sound/china.wav");
	kyoko = LoadSoundMem("files/sound/kyoko.wav");

}