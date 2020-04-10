#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "map_cell.hpp"
#include "entity.hpp"
#include "chunk.hpp"

#include <vector>

class GameMap
{
private:
  int m_width, m_height;
  std::vector<std::vector<MapCell>> m_cells;
  std::vector<Chunk> m_chunkList;

public:
  GameMap();
  MapCell *at(const Position &position);
  MapCell *at(const Entity &entity);
  MapCell *at(const Entity *entity);

  void update();
  static std::shared_ptr<GameMap> generate();
};

#endif