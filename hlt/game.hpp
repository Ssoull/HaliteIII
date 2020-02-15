#ifndef GAME_H
#define GAME_H

#include "player.hpp"
#include "game_map.hpp"

#include <vector>

class Game
{
private:
    int m_turnNumber, m_id;
    std::vector<std::shared_ptr<Player>> m_players;
    std::shared_ptr<Player> m_me;
    std::unique_ptr<GameMap> m_gameMap;

public:
    Game();
    void ready(const std::string &name);
    void update_frame();
    bool end_turn(const std::vector<std::string> &commands);
    std::unique_ptr<GameMap> getGameMap();

    // Getter
    int getTurnNumber() const;
    int getId() const;
    std::shared_ptr<Player> getMe() const;
    std::unique_ptr<GameMap> getGameMap() const;
};

#endif