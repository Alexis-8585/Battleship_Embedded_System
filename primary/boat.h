// boat.h
#ifndef BOAT_H
#define BOAT_H


class Boat
{
    public:
        Boat(int len = 4);
        int length;
        int row;
        int col;
        bool isPlaced;
        bool isHorizontal;
        
        

        void rotate();
        bool canFit() const;
        int getNumAlive();
        int decreaseAlive();
        
    private: 
        int numAlive;

};

#endif