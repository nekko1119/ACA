#include "Animation.h"
#include <stdexcept>
using namespace aca::resource;

Animation::Animation(int fps, int start, int allNum) : index(0), fps(fps), start(start), allNum(allNum), count(0), isLoop(false) 
{
}

void Animation::update()
{
    if(fps == 0)
    {
        throw std::logic_error("fpsが0です。0除算しようとしました");
    }

    int frame = count / fps;	//ディレイ込みのカウント

    //1周したかどうか
    if(frame >= allNum)
    {
        isLoop = true;
    }

    index = frame % allNum + start;
    ++count;
}

void Animation::reset()
{
    isLoop = false;
    count = 0;
}