#ifndef COMMAND_H
#define COMMAND_H

#include "../src/position.hpp"

#include <string>

const char GENERATE = 'g';
const char CONSTRUCT[] = "c ";
const char MOVE[] = "m ";

class Command
{
public:
  static std::string spawnShip();
  static std::string transformShipIntoDropoff(const int id);
  static std::string move(const int id, const Direction direction);
};

#endif