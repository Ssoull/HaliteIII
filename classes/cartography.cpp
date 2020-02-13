#include "cartography.hpp"
#include "../hlt/log.hpp"

// Data true = ship, Data false = structure
void Cartography::markAsUnsafe(hlt::Entity entity) {
    m_ships.push_back(entity); 
}

void Cartography::markAsSafe(hlt::EntityId id) {
    int count = 0;
    bool found = false;

    while (count < m_ships.size() && !found) {
        if(m_ships[count].id == id) {
            found = true;
            hlt::log::log("[Cartography::markAsSafe] Safe cell found " + std::to_string(id));
        } else {
            ++count;
        }
    }

    if (found) {
        m_ships.erase(m_ships.begin() + count);
    }
}

void Cartography::markStructure(hlt::Entity entity) {
    m_structures.push_back(entity);
}

// void Cartography::checkUnsafeCells(){
//     std::vector<hlt::MapCell> *unsafeCells = new std::vector<hlt::MapCell>();
//     for(int x = 0; x < m_map->cells.size(); ++x){
//         for(int y = 0; y < m_map->cells[x].size(); ++y ){
//             hlt::log::log(to_string(m_map->cells[x][y].is_occupied()));
//             // if(&iit.is_occupied()){
//             //     unsafeCells->push_back(*iit);
//             // }
//             if(m_map->cells[x][y].is_occupied()){
                
//             }
//         }
//     }
//     m_unsafeCells = unsafeCells;
// }

// void Cartography::updateCartographyData(std::shared_ptr<hlt::GameMap> map/*, std::vector<hlt::Entity> entities*/){
//     hlt::log::log("Map data updated");
//     m_map = map;
//     checkUnsafeCells();
// }

std::vector<hlt::Entity> Cartography::getUnsafeCells(){
    return m_ships;
}