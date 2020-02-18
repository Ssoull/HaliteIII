#include "harvestingState.hpp"

#include "../utils/log.hpp"

void HarvestingState::update()
{
    // custom_logger::log("Update");
}

void HarvestingState::update(Ship *entityToUpdate)
{
    //Update state here with entity data
}

void HarvestingState::onStateEnter()
{
    //Actions to perform on state enter (e g : set target...)
}

void HarvestingState::onStateExit()
{
    //Actions to perform on state exit
}