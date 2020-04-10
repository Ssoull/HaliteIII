#pragma once

#include "game_map.hpp"
#include "player.hpp"
#include "types.hpp"
#include "../classes/cartography.hpp"

#include <vector>
#include <iostream>

namespace hlt {
    struct Game {
        int turn_number;
        PlayerId my_id;
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<Player> me;
        std::shared_ptr<GameMap> game_map;

        Game();
        void ready(const std::string& name);
        void update_frame(std::unique_ptr<Cartography>& carto);
        bool end_turn(const std::vector<Command>& commands);
    };
}
