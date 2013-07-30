#ifndef ACA_GAME_LAZER_H
#define ACA_GAME_LAZER_H

#include "DynamicObject.h"
#include "Animation.h"
#include <map>

namespace aca { namespace game {

class Lazer : public DynamicObject
{
public:
    enum State
    {
        Begin,
        Now,
        End
    };

    Lazer(
        std::shared_ptr<Position> position,
        Direction direction,
        aca::resource::DefaultImage image,
        aca::resource::Animation* animation,
        RECT rect
        );

    void update();
    void draw() const;
    bool getIsFinished() const {return isFinished;}

private:
    static const int Length;	//Å‘åÆËŠÔ

    std::map<State, resource::Animation> state;
    State curState;
    bool isFinished;
    int count;	//ÆËŠÔ
};

}}

#endif