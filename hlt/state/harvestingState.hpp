#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

class HarvestingState : public State
{
private:
    /* data */
public:
    virtual void update() override;
};


#endif