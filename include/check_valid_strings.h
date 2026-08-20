#include <vector>
#include <iostream>
#include <stdlib.h>
#include <map>

using namespace std;

map<char, int> hex_to_int{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15},
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
};

bool is_valid_escape(const vector<char>& str, int& index){ //reference so that it us updated by necessary amt

    //str[index] should be at the \ char when fn called

    if(index + 1 >= str.size()){
        throw std::runtime_error("you cant end a string with an escape char");
    }

    index += 1; //eat the \

    unsigned char buffer = str[index];

    if(buffer == 'u'){
        if(index+4 >= str.size()) throw std::runtime_error("must have 4 chars following u escape\n");

        unsigned char unicode[4] = {str[index+1], str[index+2], str[index+3], str[index+4]}; //standard U+xxxx

        //update index to eat the extra eaten chars. 
        index += 4;

        //do hex to binary

        unsigned int bin = 0;

        for(int dig = 0; dig < 4; dig++){

            //shift 4-dig * 4 <<

            if(!((unicode[dig] >='0' && unicode[dig] <= '9') || (unicode[dig] >= 'A' && unicode[dig] <= 'F') || (unicode[dig] >= 'a' && unicode[dig] <= 'f') )){
                throw std::runtime_error("not a hex digit\n");
            }

            bin = bin | (hex_to_int[unicode[dig]] << 4*(3-dig));

        }

        //do checks on bin validity:
        //max unicode value would be U+FFFF which is 16^4 = 65536, min is 0 

        bool is_invalid = false;

        /*
        ADD COMPAtIBILITY FOR SURROGATE CHECKS 
        /uxxx/uxxxx

        if(){ //low surrogate 0xDC00–0xDFFF. low surrogate w/o high surrogate preceding it is invalid
            
        }
        if(){ //high surrogate 0xD800–0xDBFF
            //get the low surrogate and call this function again (not recursion. i just mean it has to check it too)

        }
        */

        if(!is_invalid){
            return true;
        }else{
            throw std::runtime_error("bad unicode codepoint\n");
        }

    }else if(buffer == '"' || buffer == '\\' || buffer == '/' || buffer == 'b' || buffer == 'f' || buffer == 'n' || buffer == 'r' || buffer == 't'){
        return true;
    }else{
        throw std::runtime_error("Invalid escape sequence. not one of the allowed chars follow the \\ \n");
    }

}


//unicode checks for characters within a string

bool is_valid_string(vector<char> str){

    //check if each char in str is OK

    if(str.size() <= 0){
        throw runtime_error("Bad string passed into is_valid_string()\n");
    }

    int index = 0;
    
    unsigned char buffer;      //holds 1 byte (the current character at index)

    bool is_invalid = false;

    while(index < str.size()){

        is_invalid = false;

        buffer = str[index];

        int extra_bytes = 0; //default 0 value
        /*1 byte */ if((buffer & 0b10000000) == 0b0){
            extra_bytes = 0; //0xxxxxxx (ASCII)

            if(buffer == '\\'){
                if(is_valid_escape(str, index)){
                    index += 1; //since continue is used, this aprt is skipped at the end of the loop
                    continue;
                } // if it isnt valid, the fn shouldve thrown an exception
                
            }
        }             
        /*2 bytes*/ else if((buffer & 0b11100000) == 0b11000000) extra_bytes = 1; //110xxxxx
        /*3 bytes*/ else if((buffer & 0b11110000) == 0b11100000) extra_bytes = 2; //1110xxxx
        /*4 bytes*/ else if((buffer & 0b11111000) == 0b11110000) extra_bytes = 3; //11110xxx
        /*invalid*/ else                                         is_invalid = true;
        
        for(int i = 1; i <= extra_bytes; i++){

            if(index+i >= str.size()){
                //return 0; for tests
                throw runtime_error("Improperly formatted string. character incomplete, unable to read char and reached EOF\n");
            }

            buffer = str[index+i];
            
            if((buffer & 0b11000000) != 0b10000000){ //since must start with 10xxxxxx
                is_invalid = 1;
                //conscious decision: still continue to read thru the extra bytes of this broken character
            }
        }


        //concatenate bits without the payload and reconvert into binary
        unsigned int new_bin;

        if(is_invalid)
            new_bin = 0; //0 just so that new_bin isnt storing garbage
        else if(extra_bytes == 1) 
            new_bin = ((str[index] & 0b00011111) << 6) | (str[index+1] & 0b00111111);
        else if(extra_bytes == 2)
            new_bin = ((str[index] & 0b00001111) << 12) | ((str[index+1] & 0b00111111) << 6) | (str[index+2] & 0b00111111);
        else if(extra_bytes == 3)
            new_bin = ((str[index] & 0b00000111) << 18) | ((str[index+1] & 0b00111111) << 12) | ((str[index+2] & 0b00111111) << 6) | (str[index+3] & 0b00111111);
        else if(extra_bytes == 0)
            new_bin = str[index]; //no extra bytes
            
        //Other checks for valid bin:
        if(!is_invalid){
            if(new_bin <= 31 || new_bin == 127) is_invalid = 1; //C0 control set - for non-printables from ASCII (standard)
            if(new_bin >= 0x80 && new_bin <= 0x9F) is_invalid = 1; //C1 control set - more non printables (standard)
            if(new_bin >= 0xD800 && new_bin <= 0xDFFF) is_invalid = 1; //U+ surrogate values (see utf-16)
            if(new_bin > 0x10FFFF) is_invalid = 1; //this is the max possible unicode codepoint
            //Overlong encodings check - each sequence must use its shortest form
            if(extra_bytes == 1 && new_bin < 0x80)    is_invalid = 1; //0x80 = decimal 128 = 2^7
            if(extra_bytes == 2 && new_bin < 0x800)   is_invalid = 1; //0x800 = decimal 2048 = 2^11
            if(extra_bytes == 3 && new_bin < 0x10000) is_invalid = 1; //0x10000 = decimal 65536 = 2^16
        }

        if(is_invalid){
            //return false; for tests
            throw std::runtime_error("Error in string formatting.\n");
        }
        index += 1 + extra_bytes;
    }

    //if(is_invalid) return false;
    return true;

}