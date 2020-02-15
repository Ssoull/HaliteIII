#ifndef SHIP_H
#define SHIP_H

#include "entity.hpp"
#include "position.hpp"
#include "command.hpp"

class Ship : public Entity
{
    private:
    int m_halite;
    Position m_pos;

    public:
    Ship(const int ownerId, const int entityId, const Position &pos, const int halite);
    bool isFull();
    std::string makeDropoff() const;
    std::string move(const Direction direction) const;
    std::string stayStill() const;
    static std::shared_ptr<Ship> generate(const int playerID);
};

#endif