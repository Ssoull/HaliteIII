#ifndef SHIPYARD_H
#define SHIPYARD_H

#include "entity.hpp"
#include "command.hpp"

#include <string>

class Shipyard : public Entity
{
public:
  Shipyard(const int ownerId, const Position &pos);

  std::string spawn();
};

#endif