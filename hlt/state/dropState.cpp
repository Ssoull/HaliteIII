#include "dropState.hpp"

void DropState::update(Ship *entity_to_update, std::shared_ptr<GameMap> &game_map)  {
    //Check when the ship has arrived to the dropoff creation place
    if(willBeDropoff && entity_to_update->getPosition() == m_bestDropLocation){
        shouldCreateDropoff = true;
    }
}

void DropState::onStateEnter(std::shared_ptr<GameMap> &game_map, Ship *entity)  {
    //Cehck if there is a dropoff in surrondings
    if(checkForDropoff(game_map, DROPOFF_CHECK_RADIUS ,entity->getPosition())){
        m_bestDropLocation = m_dropoffLocation;
    }
    else{
        willBeDropoff = true;
        m_bestDropLocation = computeBestDestination(entity->getPosition(), game_map);
    }
}

void DropState::onStateExit()  {
    
}

Position DropState::getDestination()  {
    return m_bestDropLocation;
}

Position DropState::computeBestDestination(const Position &start_pos, std::shared_ptr<GameMap> &game_map)  {
    
}

bool DropState::checkForDropoff(std::shared_ptr<GameMap> &game_map, int radius, Position center){
    std::shared_ptr<std::vector<Position>> positionsInRadius = game_map->getPositionsInRadius(center, radius);
    for(int i = 0; i < positionsInRadius->size(); ++i){
        if(game_map->at((*positionsInRadius)[i])->hasDropoff()){
            m_dropoffLocation = (*positionsInRadius)[i];
            return true;
        }
    }
    return false;
}
