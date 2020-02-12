#ifndef ASTAR_H
#define ASTAR_H

#include "../hlt/map_cell.hpp"
#include "../hlt/position.hpp"

#include <vector>

class Astar {
    private : 
        std::vector<hlt::MapCell> path;
    public : 
        Astar(hlt::Position startingPos, hlt::Position destinationPos);
};

#endif