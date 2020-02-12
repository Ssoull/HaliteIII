#include "hlt/game.hpp"
#include "hlt/constants.hpp"
#include "hlt/log.hpp"
#include "classes/chunk.hpp"
#include "classes/dstar.hpp"
#include "classes/cartography.hpp"

#include <random>
#include <ctime>

using namespace std;
using namespace hlt;

int main(int argc, char* argv[]) {
    unsigned int rng_seed;
    if (argc > 1) {
        rng_seed = static_cast<unsigned int>(stoul(argv[1]));
    } else {
        rng_seed = static_cast<unsigned int>(time(nullptr));
    }
    mt19937 rng(rng_seed);


    Game game;
    // At this point "game" variable is populated with initial map data.
    // This is a good place to do computationally expensive start-up pre-processing.
    // As soon as you call "ready" function below, the 2 second per turn timer will start.
    game.ready("MyCppBot");

    log::log("Successfully created bot! My Player ID is " + to_string(game.my_id) + ". Bot rng seed is " + to_string(rng_seed) + ".");
    Chunk chunk(0, 10, game.game_map->getCells());
    chunk.getLowestCell();

    //Dstar test
    // Dstar *testDstar = new Dstar(game.game_map->width, game.game_map->height);
    Dstar *testDstar = new Dstar(6, 6);
    testDstar->init(0,0,5,5);
    list<state> myPath;
    log::log(to_string(myPath.size()));
    testDstar->replan();
    myPath = testDstar->getPath();
    

    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        shared_ptr<GameMap>& game_map = game.game_map;

        vector<Command> command_queue;

        Cartography *carto = new Cartography();
        carto->updateCartographyData(game_map);
        // log::log("Number of unsafe cells : " + to_string(carto->getUnsafeCells()->size()));

        for (const auto& ship_iterator : me->ships) {
            shared_ptr<Ship> ship = ship_iterator.second;
            if (game_map->at(ship)->halite < constants::MAX_HALITE / 10 || ship->is_full()) {
                Direction random_direction = ALL_CARDINALS[3];
                log::log("[MyBot.cpp] Ship id on movement :" + to_string(ship->id));

                command_queue.push_back(ship->moveWithPosition(Position(0, 0)));
                // command_queue.push_back(ship->move(game.game_map->naive_navigate(ship, Position(0, 0))));
            } else {
                command_queue.push_back(ship->stay_still());
            }
        }

        if (
            game.turn_number <= 200 &&
            me->halite >= constants::SHIP_COST &&
            !game_map->at(me->shipyard)->is_occupied())
        {
            command_queue.push_back(me->shipyard->spawn());
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }

    return 0;
}