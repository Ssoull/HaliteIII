#ifndef CARTOGRAPHY_H
#define CARTOGRAPHY_H

#include "../hlt/map_cell.hpp"
#include "../hlt/game_map.hpp"
#include <vector>

class Cartography {
    private:
        int m_xWidth, m_yWidth;
        hlt::GameMap m_map;
        std::vector<hlt::MapCell> *m_unsafeCells;
        void checkUnsafeCells();
    public:
        Cartography();
        std::vector<hlt::MapCell> *getUnsafeCells();
        void updateCartographyData(hlt::GameMap map);
};

#endif