#include "cartography.hpp"
#include "../hlt/log.hpp"


Cartography::Cartography(){
}

void Cartography::checkUnsafeCells(){
    std::vector<hlt::MapCell> *unsafeCells = new std::vector<hlt::MapCell>();
    for(int x = 0; x < m_map->cells.size(); ++x){
        for(int y = 0; y < m_map->cells[x].size(); ++y ){
            hlt::log::log(to_string(m_map->cells[x][y].is_occupied()));
            // if(&iit.is_occupied()){
            //     unsafeCells->push_back(*iit);
            // }
            if(m_map->cells[x][y].is_occupied()){
                
            }
        }
    }
    m_unsafeCells = unsafeCells;
}

void Cartography::updateCartographyData(shared_ptr<hlt::GameMap> map/*, std::vector<hlt::Entity> entities*/){
    hlt::log::log("Map data updated");
    m_map = map;
    checkUnsafeCells();
}

std::vector<hlt::MapCell> *Cartography::getUnsafeCells(){
    return m_unsafeCells;
}