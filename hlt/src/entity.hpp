#ifndef ENTITY_H
#define ENTITY_H

#include "position.hpp"

class Entity
{
protected:
  int m_playerID, m_entityId;
  Position m_position;

public:
  Entity(const int ownerId, const int entityId, const Position &pos);

  // Getter
  Position getPosition() const;
  int getId() const;
};

#endif
