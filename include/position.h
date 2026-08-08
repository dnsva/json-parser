
#ifndef POSITION_H
#define POSITION_H

struct Position{ //of the json or text file
    int row{};
    int col{};
    bool exists = false;


    Position() : exists{false} {}

    Position(int n) : row{n}, exists{true} {}

    int pos_to_index(){
        return row*col + col;
    }

    int operator+(int n){ //[pos_obj]++ should just add to col
        col += n;
        return col;
    }

    Position operator++(int){
        Position temp = *this;
        this->col++;
        return temp;
    }

};

#endif