#include "hlt/src/game.hpp"
#include "hlt/utils/constants.hpp"
#include "hlt/utils/log.hpp"

#include <random>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
  unsigned int rng_seed;
  if (argc > 1)
  {
    rng_seed = static_cast<unsigned int>(stoul(argv[1]));
  }
  else
  {
    rng_seed = static_cast<unsigned int>(time(nullptr));
  }
  mt19937 rng(rng_seed);

  Game game;
  // At this point "game" variable is populated with initial map data.
  // This is a good place to do computationally expensive start-up pre-processing.
  // As soon as you call "ready" function below, the 2 second per turn timer will start.
  game.ready("MyCppBot");

  custom_logger::log("Successfully created bot! My Player ID is " + to_string(game.getId()) + ". Bot rng seed is " + to_string(rng_seed) + ".");

  for (;;)
  {
    game.update_frame();
    shared_ptr<Player> me = game.getMe();
    shared_ptr<GameMap> game_map = game.getGameMap();

    vector<std::string> command_queue;

    for (const auto &ship_iterator : me->getShips())
    {
      shared_ptr<Ship> ship = ship_iterator.second;
      if (game_map->at(ship.get())->getHalite() < constants::MAX_HALITE / 10 || ship->isFull())
      {
        command_queue.push_back(ship->move(Direction::East));
      }
      else
      {
        command_queue.push_back(ship->stayStill());
      }
    }

    if (
        game.getTurnNumber() <= 200 &&
        me->getHalite() >= constants::SHIP_COST &&
        !game_map->at(me->getShipyard().get())->hasShip())
    {
      command_queue.push_back(me->getShipyard()->spawn());
    }

    if (!game.end_turn(command_queue))
    {
      break;
    }
  }

  return 0;
}
