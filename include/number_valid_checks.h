//.6e4e..4htnv6ryfmhvgrtrytrreeeeeeeeeeEEE
//num limits - e.g., 1 million 1s ???
//tdd = text driven development


#include <iostream>
#include <regex> //cpp 11
#include <string.h>

/*

pattern: 

-?(?:0|[1-9]\d*)(?:\.\d+)?(?:[eE][+-]?\d+)?

explains all the valid numbers

*/

using namespace std;


bool is_valid_number(const vector<char>& number){

    const regex rule("-?(?:0|[1-9]\\d*)(?:\\.\\d+)?(?:[eE][+-]?\\d+)?");

    //use match function

    //if match isnt perfect then throw invalid otherwise true
    bool is_valid = regex_match(string(number.begin(), number.end()), rule);

    if(is_valid) return true;
    throw std::runtime_error("Invalid number format.\n");
    //return 0; //for testing

}