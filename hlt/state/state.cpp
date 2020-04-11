#include "state.hpp"

State::State() {}

void State::update()
{
}

void State::update(Ship *shipToUpdate)
{
}
void State::update(Ship *shipToUpdate, std::shared_ptr<GameMap> &game_map){

}

void State::onStateEnter()
{
}

void State::onStateExit()
{
}

Direction State::computeNextDirection(const Position &dest, std::shared_ptr<GameMap> &game_map)
{
    return Direction::Still;
}

Position State::computeBestDestination(const Position &startPosition, std::shared_ptr<GameMap> &game_map)
{
    return Position(0,0);
}

Position State::getDestination(){
    return Position(0,0);
}