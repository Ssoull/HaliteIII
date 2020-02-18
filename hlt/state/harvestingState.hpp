#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

class HarvestingState : public State
{
private:
    /* data */
public:
    virtual void update() override;
    virtual void update(Ship *entityToUpdate) override;
    virtual void onStateEnter() override;
    virtual void onStateExit() override;
};

#endif