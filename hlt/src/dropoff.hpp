#ifndef DROPOFF_H
#define DROPOFF_H

#include "position.hpp"
#include "entity.hpp"

class Dropoff : public Entity
{
public:
  Dropoff(const int ownerId, const int entityId, const Position &pos);

  static std::shared_ptr<Dropoff> generate(const int playerId);
};

#endif