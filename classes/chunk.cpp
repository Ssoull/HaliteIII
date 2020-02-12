#include "../hlt/log.hpp"
#include "../hlt/constants.hpp"
#include "chunk.hpp"

#include <climits>

Chunk::Chunk(int coordX, int coordY, std::vector< std::vector<hlt::MapCell> > chunkData) : m_coordX(coordX), m_coordY(coordY) {
    hlt::log::log("[Chunk::constructor] Chunk : Position (" + std::to_string(m_coordX) + ", " + std::to_string(m_coordY) + ")");
    computeData(chunkData);
}

void Chunk::computeData(std::vector< std::vector<hlt::MapCell> > chunkData) {
    //Compute the average halite value in this chunk
    //and assign the cell with the lowest halite value to set a dropoff on this cell
    hlt::MapCell* tempCell = new hlt::MapCell(0, 0, INT_MAX);
    int haliteSum = 0;
    for(int i = m_coordX; i < SIZE_CHUNK; ++i){
        for(int j = m_coordY; j < SIZE_CHUNK; ++j){
            if(chunkData[i][j].halite < tempCell->halite){
                tempCell = &chunkData[i][j];
            }
            
            haliteSum += chunkData[i][j].halite;
        }
    }

    m_averageHaliteValueFloat = haliteSum/(SIZE_CHUNK*SIZE_CHUNK);
    hlt::log::log("[Chunk::computeData] Average Value : " + std::to_string(m_averageHaliteValueFloat));

    m_mapCell = std::unique_ptr<hlt::MapCell>(new hlt::MapCell(*tempCell));
    hlt::log::log("[Chunk::computeData] Lowest value : " + std::to_string(m_mapCell-> halite) + " Coords : (x :"+std::to_string(m_mapCell -> position.x)+",y :"+std::to_string(m_mapCell -> position.y)+")");
}


hlt::MapCell Chunk::getLowestCell() {
    hlt::log::log("[Chunk::getLowestCell] Lowest cell position (" + std::to_string(m_mapCell->position.x) + ", " + std::to_string(m_mapCell->position.y) + "), halite amount : " + std::to_string(m_mapCell->halite));
    
    return *m_mapCell;
}


float Chunk::getChunkAverageValue() {
    hlt::log::log("[Chunk::getChunkAverageValue] Average Value : " + std::to_string(m_averageHaliteValueFloat));

    return m_averageHaliteValueFloat;
}
void Chunk::updateChunk(std::vector< std::vector<hlt::MapCell> > chunkData) {
    computeData(chunkData);
}