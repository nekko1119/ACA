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
        throw std::logic_error("fps��0�ł��B0���Z���悤�Ƃ��܂���");
    }

    int frame = count / fps;	//�f�B���C���݂̃J�E���g

    //1���������ǂ���
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