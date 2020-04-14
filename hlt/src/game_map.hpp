#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "map_cell.hpp"
#include "entity.hpp"
#include "chunk.hpp"
#include "dstar.hpp"

#include <vector>

class GameMap
{
private:
  int m_width, m_height;
  std::vector<std::vector<MapCell>> m_cells;
  std::vector<Chunk> m_chunkList;
  std::vector<Position> m_unsafeCells;

public:
  GameMap(const int width, const int height);
  MapCell *at(const Position &position);
  MapCell *at(const Entity &entity);
  MapCell *at(const Entity *entity);

  void update();
  static std::shared_ptr<GameMap> generate();

  int computeManathanDistance(const Position &p1, const Position &p2) const;

  //Normalize positions to use wrap around map coordinates
  Position normalizePosition(int x, int y);
  // Getters
  int getWidth() const;
  int getHeight() const;
  int getTotalHalite() const;
  double getCost(const Position &pos) const;

  //Return all the positions in the given radius around the radius center parameter
  std::vector<Position> getPositionsInRadius(Position radiusCenter, int radius);
};

#endif