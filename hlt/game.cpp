#include "game.hpp"

#include "input.hpp"
#include "constants.hpp"
#include "log.hpp"

Game::Game() : m_turnNumber(0)
{
  std::ios_base::sync_with_stdio(false);
  constants::populate_constants(input::get_string());

  int num_players;
  std::stringstream input(input::get_string());
  input >> num_players >> m_id;

  custom_logger::open(m_id);

  for (int i = 0; i < num_players; ++i)
  {
    m_players.push_back(Player::generate());
  }
  m_me = m_players[m_id];
  m_gameMap = GameMap::generate();
}

void Game::ready(const std::string &name)
{
  std::cout << name << std::endl;
}

void Game::update_frame()
{
  input::get_sstream() >> m_turnNumber;
  custom_logger::log("=============== TURN " + std::to_string(m_turnNumber) + " ================");

  for (size_t i = 0; i < m_players.size(); ++i)
  {
    int current_player_id, num_ships, num_dropoffs, halite;

    input::get_sstream() >> current_player_id >> num_ships >> num_dropoffs >> halite;

    m_players[current_player_id]->update(num_ships, num_dropoffs, halite);
  }

  m_gameMap->update();

  for (const auto &player : m_players)
  {
    for (auto &ship_iterator : player->getShips())
    {
      auto ship = ship_iterator.second;
      m_gameMap->at(*ship)->markShip(true);
    }

    m_gameMap->at(*player->getShipyard())->markShipYard(true);

    for (auto &dropoff_iterator : player->getDropoffs())
    {
      auto dropoff = dropoff_iterator.second;
      m_gameMap->at(*dropoff)->markDropoff(true);
    }
  }
}

bool Game::end_turn(const std::vector<std::string> &commands)
{
  for (const auto &command : commands)
  {
    std::cout << command << ' ';
  }
  std::cout << std::endl;
  return std::cout.good();
}

// Getter
int Game::getTurnNumber() const
{
  return m_turnNumber;
}

int Game::getId() const
{
  return m_id;
}

std::shared_ptr<Player> Game::getMe() const
{
  return m_me;
}

std::shared_ptr<GameMap> Game::getGameMap() const
{
  return m_gameMap;
}
