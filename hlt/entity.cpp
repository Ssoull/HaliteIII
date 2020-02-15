#include "entity.hpp"

Entity::Entity(const int ownerId, const  int entityId, const Position &pos) : m_playerID(ownerId), m_entityId(entityId), m_position(pos) {}

Position Entity::getPosition() const 
{
    return m_position;
}

int Entity::getId() const 
{
    return m_entityId;
}