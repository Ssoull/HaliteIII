#ifndef STATE_H
#define STATE_H

#include "../entity.hpp"

class State
{
private:
public:
    State();
    virtual void update();
    virtual void update(Entity *entityToUpdate);
    virtual void onStateEnter();
    virtual void onStateExit();
};
#endif