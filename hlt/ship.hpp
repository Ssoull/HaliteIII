#pragma once

#include "entity.hpp"
#include "constants.hpp"
#include "command.hpp"

#include "../classes/dstar.hpp"

#include <memory>

namespace hlt {
    struct Ship : Entity {
        Halite halite;
        unique_ptr<Dstar> pathToGoal;
        int numOfShip;

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

        Command moveWithPosition(Position pos) {
            pathToGoal->init(position.x, position.y, pos.x, pos.y);
            pathToGoal->replan();
            list<state> list = pathToGoal->getPath();
            list.pop_front();

            state nextStep;
            if (!list.empty()) {
                nextStep = list.front();
            } else {
                nextStep.x = position.x;
                nextStep.y = position.y;
            }

            log::log("NEXTSTEP : " + std::to_string(nextStep.x) + ", " + std::to_string(nextStep.y));
            log::log("CURRENT : " + std::to_string(position.x) + ", " + std::to_string(position.y));

            int tempX = nextStep.x - position.x;
            int tempY = nextStep.y - position.y;
            if(tempX != 0){
                if(tempX){
                    return hlt::command::move(id, hlt::Direction::WEST);
                }
                else{
                    return hlt::command::move(id, hlt::Direction::EAST);
                }
            }
            if(tempY !=0){
                if(tempY){
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
