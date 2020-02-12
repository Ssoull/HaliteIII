#include "cartography.hpp"
#include "../hlt/log.hpp"


Cartography::Cartography(){
}

void Cartography::checkUnsafeCells(){
    std::vector<hlt::MapCell> *unsafeCells = new std::vector<hlt::MapCell>();
    for(std::vector<std::vector<hlt::MapCell>>::iterator it = m_map.cells.begin(); it != m_map.cells.end(); ++it){
        for(std::vector<hlt::MapCell>::iterator iit = it->begin(); iit != it->end(); ++iit ){
            hlt::log::log(to_string(iit->is_occupied));
            if(iit->is_occupied()){
                unsafeCells->push_back(*iit);
            }
        }
    }
    m_unsafeCells = unsafeCells;
}

void Cartography::updateCartographyData(hlt::GameMap map){
    hlt::log::log("Map data updated");
    m_map = map;
    checkUnsafeCells();
}

std::vector<hlt::MapCell> *Cartography::getUnsafeCells(){
    return m_unsafeCells;
}