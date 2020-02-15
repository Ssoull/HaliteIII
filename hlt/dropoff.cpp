#include "dropoff.hpp"

#include "input.hpp"

Dropoff::Dropoff(const int ownerId, const int entityId, const Position &pos) : Entity(ownerId, entityId, pos) {}

std::shared_ptr<Dropoff> Dropoff::generate(const int playerId)
{
  int dropoff_id, x, y;

  input::get_sstream() >> dropoff_id >> x >> y;

  return std::make_shared<Dropoff>(playerId, dropoff_id, Position(x, y));
}
