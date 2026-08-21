#include "../include/check_valid_strings.h"
#include <iostream>

using namespace std;

int main(){

    //valid
    cout<<is_valid_string(vector<char>{'\x61'});//'a'
    cout<<is_valid_string(vector<char>{'\xC3', '\xA9'});//é
    cout<<is_valid_string(vector<char>{'\xF0', '\x9F', '\x98', '\x80'});//😀

    string test_string = "\\uD83D\\uDE00";
    cout<<is_valid_string(vector<char>{test_string.begin(), test_string.end()});
    
    //invalid 
    
    cout<<is_valid_string(vector<char>{'\xA9'});//lone continuation
    cout<<is_valid_string(vector<char>{'\xC3'});//truncated
    cout<<is_valid_string(vector<char>{'\xC3', '\x41'});//non-continuation byte
    cout<<is_valid_string(vector<char>{'\xE0', '\xA9'});//truncated 3-byte
    cout<<is_valid_string(vector<char>{'\xC0', '\x80'});//overlong U+0000
    cout<<is_valid_string(vector<char>{'\xC1', '\xBF'});//overlong encoding
    cout<<is_valid_string(vector<char>{'\xE0', '\x80', '\x80'});//overlong 3-byte
    cout<<is_valid_string(vector<char>{'\xED', '\xA0', '\x80'});//surrogate U+D800
    cout<<is_valid_string(vector<char>{'\xED', '\xBF', '\xBF'});//surrogate U+DFFF
    cout<<is_valid_string(vector<char>{'\xF4', '\x90', '\x80', '\x80'});//out of range
    cout<<is_valid_string(vector<char>{'\xF5', '\x80', '\x80', '\x80'});//invalid F5
    cout<<is_valid_string(vector<char>{'\xFF'});//invalid FF
    
}