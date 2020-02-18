#ifndef STATE_H
#define STATE_H

// Error of cyclic dependency between state and ship
class Ship;

class State
{
private:
public:
    State();
    virtual void update();
    virtual void update(Ship *shipToUpdate);
    virtual void onStateEnter();
    virtual void onStateExit();
};
#endif