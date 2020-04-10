#ifndef CHUNK_H
#define CHUNK_H

#include "position.hpp"

class Chunk {
    private: 
        Position topLeftPosition; //Top left coordinates of the chunk
        int size; //Size of the chunk, as it's a square height and width are the same
        int halite; //amount of halite in chunk
        int avgHalite; //Average amount of halite in chunk
        Position highestHalite; //position of the cell with the highest amount of halite in the chunk
    public:
        Chunk(int x, int y, int size);
        Chunk(Position p, int size);
        //Getters 
        int getSize();
        int getHalite();
        int getAvgHalite();
        Position getHighestHalitePosition();
        Position getPosition();

        //Setters
        void setHalite(int halite);
        void setAvgHalite(int avgHalite);
        void setHighestHalitePosition(Position p);
        void setHighestHalitePosition(int x, int y);
};

#endif