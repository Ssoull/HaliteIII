#include "command.hpp"

std::string Command::spawnShip()
{
  return std::string(1, GENERATE);
}

std::string Command::transformShipIntoDropoff(const int id)
{
  return CONSTRUCT + std::to_string(id);
}

std::string Command::move(const int id, const Direction direction)
{
  return MOVE + std::to_string(id) + ' ' + static_cast<char>(direction);
}