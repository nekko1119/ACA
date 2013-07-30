#ifndef ACA_GAME_LIFE_H
#define ACA_GAME_LIFE_H

namespace aca { namespace game {

class Life
{
public:
    explicit Life(int life);

    void reduce(int damege);
    int get() const {return life;}
    bool isDead() const;

private:
    int life;
};

}}

#endif