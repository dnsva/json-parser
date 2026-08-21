
#ifndef POSITION_H
#define POSITION_H

#include <iostream>

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

/*

super wrong. do error handling later 

void print_line(Position p, ifstream& file){ //make sure file pos is restored

    auto saved_pos = file.tellg();

    string line;

    file.seekg(p.row*p.col + p.col);
    file.getline(line, p.col+1);

    std::cout<<line<<"\n";

}

*/

#endif