#include "chunk.hpp"

Chunk::Chunk(int x, int y, int size) : topLeftPosition(Position(x, y)), size(size) {}
Chunk::Chunk(Position p, int size) : topLeftPosition(p), size(size) {}

//Getters

int Chunk::getHalite()
{
    return halite;
}

int Chunk::getAvgHalite()
{
    return avgHalite;
}

int Chunk::getSize()
{
    return size;
}

Position Chunk::getHighestHalitePosition()
{
    return highestHalite;
}

Position Chunk::getPosition()
{
    return topLeftPosition;
}
//Setters

void Chunk::setAvgHalite(int avgHaliteValue)
{
    avgHalite = avgHaliteValue;
}

void Chunk::setHalite(int halite)
{
    halite = halite;
}

void Chunk::setHighestHalitePosition(Position p)
{
    highestHalite = p;
}

void Chunk::setHighestHalitePosition(int x, int y)
{
    highestHalite = Position(x, y);
}