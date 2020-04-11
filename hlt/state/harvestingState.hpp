#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

class HarvestingState : public State
{
private:
    /* data */
    Position bestPosition;
public:
    virtual void update() override;
    virtual void update(Ship *entityToUpdate) override;
    virtual void update(Ship *shipToUpdate, std::shared_ptr<GameMap> &game_map) override;
    virtual Position computeBestDestination(const Position &startPos, std::shared_ptr<GameMap> &game_map) override;
    virtual void onStateEnter() override;
    virtual void onStateExit() override;
    virtual Position getDestination() override;
};

#endif