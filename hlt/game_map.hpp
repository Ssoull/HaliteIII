#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "map_cell.hpp"
#include "entity.hpp"

#include <vector>

class GameMap
{
    private:
    int m_width, m_height;
    std::vector<std::vector<MapCell>> m_cells;

    public:

    MapCell *at(const Position &position);
    MapCell *at(const Entity &entity);
    MapCell *at(const Entity *entity);

    void update();
    static std::unique_ptr<GameMap> generate();
};

#endif