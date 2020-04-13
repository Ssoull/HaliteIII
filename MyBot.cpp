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
  mt19937 rng(12345678);

  Game game;
  // At this point "game" variable is populated with initial map data.
  // This is a good place to do computationally expensive start-up pre-processing.
  // As soon as you call "ready" function below, the 2 second per turn timer will start.
  game.ready("MyCppBot");

  custom_logger::log("Successfully created bot! My Player ID is " + to_string(game.getId()) + ". Bot rng seed is " + to_string(rng_seed) + ".");
  bool spawn = false;
  for (;;)
  {
    game.update_frame();

    shared_ptr<Player> me = game.getMe();
    shared_ptr<GameMap> game_map = game.getGameMap();

    vector<std::string> command_queue;
    for (const auto &ship_iterator : me->getShips())
    {
      shared_ptr<Ship> ship = ship_iterator.second;

      //Nouveau point d'entrée ?
      //Passer la map à cette fonction, derrière combiner les states et le compute nextdirection pour choisir la destination et la prochaine direction
      //Sorte d'interface pour virer toutes les décisions du mybot
      command_queue.push_back(ship->update(game_map));

      // if (game_map->at(*ship)->getHalite() / 10 < ship->getHalite() || game_map->at(*ship)->hasStructure() || ship->isFull())
      // {
      //   // command_queue.push_back(ship->move(Direction::North));
      //   command_queue.push_back(ship->move(ship->computeNextDirection(Position(0, 0), game_map)));
      // }
      // else
      // {
      //   command_queue.push_back(ship->stayStill());
      // }
    }

    if (
        game.getTurnNumber() <= 200 && //No ship spawn after game turn 200
        me->getHalite() >= constants::SHIP_COST && //We check that there is enough halite is stock
        !game_map->at(me->getShipyard().get())->hasShip() && //We check that there is no ship on shipyard
        game_map->getTotalHalite() >= game.getInitialHalite()*0.33) //No ship spawn when there's less than 33% of initial halite remaining
    {
      spawn = true;
      command_queue.push_back(me->getShipyard()->spawn());
    }

    if (!game.end_turn(command_queue))
    {
      break;
    }
  }

  return 0;
}
