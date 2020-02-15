#include "shipyard.hpp"
  
Shipyard::Shipyard(const int ownerId, const Position &pos) : Entity(ownerId, -1, pos) {}

std::string Shipyard::spawn() 
{
  return Command::spawnShip();
}