
#ifndef POSITION_H
#define POSITION_H

struct Position{ //of the json or text file
    int row{};
    int col{};
    bool exists = false;


    Position() : exists{false} {}

    Position(int n) : row{n}, exists{true} {}

    Position operator++(int){
        Position temp = *this;
        this->col++;
        return temp;
    }

};

#endif