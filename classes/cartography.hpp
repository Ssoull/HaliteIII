#ifndef CARTOGRAPHY_H
#define CARTOGRAPHY_H

#include "../hlt/map_cell.hpp"
#include "../hlt/game_map.hpp"
#include "../hlt/entity.hpp"
#include <vector>

class Cartography {
    private:
        int m_xWidth, m_yWidth;
        shared_ptr<hlt::GameMap> m_map;
        std::vector<hlt::MapCell> *m_unsafeCells;
        void checkUnsafeCells();
        void markUnsafe(hlt::Entity unsafeEntity);
    public:
        Cartography();
        std::vector<hlt::MapCell> *getUnsafeCells();
        void updateCartographyData(shared_ptr<hlt::GameMap> map/*, std::vector<hlt::Entity> entites*/);
};

#endif