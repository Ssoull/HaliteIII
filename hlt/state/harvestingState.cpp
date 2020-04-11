#include "harvestingState.hpp"

#include "../utils/log.hpp"

void HarvestingState::update()
{
    // custom_logger::log("Update");
}

void HarvestingState::update(Ship *entityToUpdate){

}

void HarvestingState::update(Ship *entityToUpdate, std::shared_ptr<GameMap> &game_map)
{
    //Update state here with entity data
    bestPosition = computeBestDestination(Position(0,0),game_map);
}

void HarvestingState::onStateEnter()
{
    //Actions to perform on state enter (e g : set target...)
}

void HarvestingState::onStateExit()
{
    //Actions to perform on state exit
}

Position HarvestingState::computeBestDestination(const Position &startPos, std::shared_ptr<GameMap> &game_map)
{
    Position bestPositionTemp = Position(0,0);
    int maxHalite = 0;
    for(int x = 0; x < game_map->getWidth(); ++x){
        for(int y = 0; y < game_map->getHeight();++y){
            if(game_map->at(Position(x,y))->getHalite() > maxHalite){
                bestPositionTemp = Position(y,x);
                maxHalite = game_map->at(Position(x,y))->getHalite();
            }
        }
    }
    custom_logger::log("HarvestingState::computeBestDestination" + bestPositionTemp.to_string());
    return bestPositionTemp; 
}

Position HarvestingState::getDestination(){
    return bestPosition;
}