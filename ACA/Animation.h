#ifndef ACA_RESOURCE_H
#define ACA_RESOURCE_H

namespace aca { namespace resource {

class Animation
{
public:
    Animation(int fps, int start, int allNum);
    void update();
    int getIndex() const {return index;}
    bool getIsLoop() const {return isLoop;}
    void reset();

private:
    int index;
    int fps;
    int start;
    int allNum;
    int count;
    bool isLoop;
};

}}

#endif