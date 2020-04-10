#include <algorithm>
#include "game_map.hpp"
#include "../utils/input.hpp"

GameMap::GameMap()
{
}

MapCell *GameMap::at(const Position &position)
{
  return &m_cells[position.getXCoord()][position.getYCoord()];
}

MapCell *GameMap::at(const Entity &entity)
{
  return (at(entity.getPosition()));
}

MapCell *GameMap::at(const Entity *entity)
{
  return at(entity->getPosition());
}

void GameMap::update()
{
  for (int y = 0; y < m_height; ++y)
  {
    for (int x = 0; x < m_width; ++x)
    {
      m_cells[y][x].markShip(false);
    }
  }
  int update_count;
  input::get_sstream() >> update_count;

  for (int i = 0; i < update_count; ++i)
  {
    int x, y, halite;
    input::get_sstream() >> x >> y >> halite;
    m_cells[y][x].setHalite(halite);
  }
}

std::shared_ptr<GameMap> GameMap::generate()
{
  std::shared_ptr<GameMap> map = std::make_shared<GameMap>();

  input::get_sstream() >> map->m_width >> map->m_height;

  map->m_cells.resize((size_t)map->m_width);
  for (int x = 0; x < map->m_width; ++x)
  {
    auto in = input::get_sstream();

    map->m_cells[x].reserve((size_t)map->m_height);
    for (int y = 0; y < map->m_height; ++y)
    {
      int halite;
      in >> halite;

      map->m_cells[x].push_back(MapCell(Position(x, y), halite));
    }
  }
  return map;
}

// Getters
int GameMap::getWidth() const
{
  return m_width;
}

int GameMap::getHeight() const
{
  return m_height;
}

std::vector<Position> GameMap::getUnsafeCells(bool includeShipyard, bool includeDropoffs)
{
  m_unsafeCells.clear();

  for (int x = 0; x < m_cells.size(); ++x)
  {
    for (int y = 0; y < m_cells[x].size(); ++y)
    {
      if (m_cells[x][y].hasStructure())
      {
        //Check if the cell has a shipyard on it
        //If yes and if we want to include the shipyard in unsafe cells it's added to the list
        if (m_cells[x][y].hasShipyard() && includeShipyard)
        {
          m_unsafeCells.push_back(m_cells[x][y].getPosition());
        }

        //Check for dropoffs if the dropoffs are included in the cells to mark as unsafe
        if (m_cells[x][y].hasDropoff() && includeDropoffs)
        {
          m_unsafeCells.push_back(m_cells[x][y].getPosition());
        }
      }

      //Check for other ships
      if (m_cells[x][y].hasShip())
      {
        m_unsafeCells.push_back(m_cells[x][y].getPosition());
      }
    }
  }

  return m_unsafeCells;
}
