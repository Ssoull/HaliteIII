#ifndef HARVESTINGSTATE_H
#define HARVESTINGSTATE_H

#include "state.hpp"

class HarvestingState : public State
{
private:
    /* data */
    Position m_bestPosition;

public:
    virtual void update() override;
    virtual void update(Ship *entity_to_update) override;
    virtual void update(Ship *ship_to_update, std::shared_ptr<GameMap> &game_map) override;
    virtual void onStateEnter() override;
    virtual void onStateExit() override;
    virtual Position computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map) override;

    // Getter
    virtual Position getDestination() override;
};

#endif