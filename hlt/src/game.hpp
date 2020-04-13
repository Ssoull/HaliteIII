#ifndef GAME_H
#define GAME_H

#include "player.hpp"
#include "game_map.hpp"

#include <vector>

class Game
{
private:
  int m_turnNumber, m_id, m_initialHalite;
  std::vector<std::shared_ptr<Player>> m_players;
  std::shared_ptr<Player> m_me;
  std::shared_ptr<GameMap> m_gameMap;

public:
  Game();
  void ready(const std::string &name);
  void update_frame();
  bool end_turn(const std::vector<std::string> &commands);

  // Getter
  int getTurnNumber() const;
  int getId() const;
  int getInitialHalite() const;
  std::shared_ptr<Player> getMe() const;
  std::shared_ptr<GameMap> getGameMap() const;
};

#endif