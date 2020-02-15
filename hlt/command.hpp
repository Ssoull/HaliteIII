#ifndef COMMAND_H
#define COMMAND_H

#include <string>

const char GENERATE = 'g';
const char CONSTRUCT[] = "c ";
const char MOVE[] = "m ";

class Command
{
public:
    static std::string staticSpawnShip();
    static std::string staticTransformShipIntoDropoff(int id);
    static std::string move(int id);
};

#endif