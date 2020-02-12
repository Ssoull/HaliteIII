#ifndef CHUNK_H
#define CHUNK_H

#include "../hlt/map_cell.hpp"

#include <vector>

const int SIZE_CHUNK = 4;

class Chunk {
private :
    int m_coordX, m_coordY;
    float m_averageHaliteValueFloat;
    std::unique_ptr<hlt::MapCell> m_mapCell;

    void computeData(std::vector< std::vector<hlt::MapCell> > chunkData);

public:
    Chunk(int coordX, int coordY, std::vector< std::vector<hlt::MapCell> > chunkData);
    
    // GETTER
    hlt::MapCell getLowestCell(); //Used to find the cell with the lowest halite value to set a dropoff on it
    float getChunkAverageValue(); //Compute the average halite value in the chunk
    void updateChunk(std::vector< std::vector<hlt::MapCell> > chunkData);
};

#endif