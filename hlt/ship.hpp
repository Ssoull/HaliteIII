#pragma once

#include "../classes/cartography.hpp"
#include "entity.hpp"
#include "constants.hpp"
#include "command.hpp"

#include "../classes/dstar.hpp"
#include <memory>

namespace hlt {
    struct Ship : Entity {
        Halite halite;
        std::unique_ptr<Dstar> pathToGoal;

        Ship(PlayerId player_id, EntityId ship_id, int x, int y, Halite halite, int game_width, int game_height) :
            Entity(player_id, ship_id, x, y),
            halite(halite),
            pathToGoal(std::unique_ptr<Dstar>(new Dstar(game_width, game_height)))
        {}

        bool is_full() const {
            return halite >= constants::MAX_HALITE;
        }

        Command make_dropoff() const {
            return hlt::command::transform_ship_into_dropoff_site(id);
        }

        Command move(Direction direction) const {
            return hlt::command::move(id, direction);
        }

        Command moveWithPosition(Position pos, std::unique_ptr<Cartography>& carto) {
            pathToGoal->init(position.x, position.y, pos.x, pos.y);

            std::vector<hlt::Entity> unsafeCells = carto->getUnsafeCells();

            log::log("Current cell : " + std::to_string(position.x) + ", " + std::to_string(position.y));
            for (int i = 0; i <unsafeCells.size(); ++i) {
                if (position != unsafeCells[i].position) {
                    pathToGoal->updateCell(unsafeCells[i].position.x, unsafeCells[i].position.y, -1);
                }
                
                log::log("Unsafe Cells : " + std::to_string(unsafeCells[i].position.x) + ", " + std::to_string(unsafeCells[i].position.y));
            }
            

            if(!pathToGoal->replan()){
                return hlt::command::move(id, hlt::Direction::STILL);
            }
            list<state> list = pathToGoal->getPath();
            list.pop_front();

            state nextStep;
            if (!list.empty()) {
                nextStep = list.front();
            } else {
                nextStep.x = position.x;
                nextStep.y = position.y;
            }

            log::log("NEXTSTEP : " + std::to_string(nextStep.x) + ", " + std::to_string(nextStep.y) + ", ID SHIP : " + std::to_string(id));
            log::log("CURRENT : " + std::to_string(position.x) + ", " + std::to_string(position.y));

            // carto->markAsSafe(id);
            carto->markAsUnsafe(Entity(owner, id, nextStep.x, nextStep.y));

            int tempX = nextStep.x - position.x;
            int tempY = nextStep.y - position.y;
            if(tempX != 0){
                if(tempX < 0){
                    return hlt::command::move(id, hlt::Direction::WEST);
                }
                else{
                    return hlt::command::move(id, hlt::Direction::EAST);
                }
            }
            if(tempY !=0){
                if(tempY < 0){
                    return hlt::command::move(id, hlt::Direction::NORTH);
                }
                else{
                    return hlt::command::move(id, hlt::Direction::SOUTH);
                }
            }

            return hlt::command::move(id, hlt::Direction::STILL);
        }

        Command stay_still() const {
            return hlt::command::move(id, Direction::STILL);
        }

        static std::shared_ptr<Ship> _generate(PlayerId player_id, int game_width, int game_height);
    };
}
