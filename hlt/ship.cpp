#include "ship.hpp"
#include "constants.hpp"
#include "input.hpp"

Ship::Ship(const int ownerId, const int entityId, const Position &pos, const int halite): Entity(ownerId, entityId, pos)
{
    m_pos = pos;
}

bool Ship::isFull()
{
    return m_halite >= constants::MAX_HALITE;
}

std::string Ship::makeDropoff() const 
{
    return Command::transformShipIntoDropoff(m_entityId);
}

std::string Ship::move(const Direction direction) const
{
    return Command::move(m_entityId, direction);
}

std::string Ship::stayStill() const
{
    return Command::move(m_entityId, Direction::STILL);
}

std::shared_ptr<Ship> Ship::generate(const int playerId)
{
    int ship_id, x, y, halite;  
    input::get_sstream() >> ship_id >> x >> y >> halite;
    return std::make_shared<Ship>(playerId, ship_id, Position(x, y), halite);
}