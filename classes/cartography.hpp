#ifndef CARTOGRAPHY_H
#define CARTOGRAPHY_H

#include "../hlt/entity.hpp"
#include <vector>

class Cartography {
    private:
        int m_xWidth, m_yWidth;
        std::vector<hlt::Entity> m_ships;
        std::vector<hlt::Entity> m_structures;
        // std::vector<hlt::MapCell> *m_unsafeCells;
        // void checkUnsafeCells();
        // void markUnsafe(hlt::Entity unsafeEntity);
    public:
        void markAsUnsafe(hlt::Entity entity);
        void markStructure(hlt::Entity entity);
        void markAsSafe(hlt::EntityId id);
        std::vector<hlt::Entity> getUnsafeCells();
        // void updateCartographyData(std::shared_ptr<hlt::GameMap> map/*, std::vector<hlt::Entity> entites*/);
};

#endif