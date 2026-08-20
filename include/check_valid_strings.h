#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

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
        }             
        /*2 bytes*/ else if((buffer & 0b11100000) == 0b11000000) extra_bytes = 1; //110xxxxx
        /*3 bytes*/ else if((buffer & 0b11110000) == 0b11100000) extra_bytes = 2; //1110xxxx
        /*4 bytes*/ else if((buffer & 0b11111000) == 0b11110000) extra_bytes = 3; //11110xxx
        /*invalid*/ else                                         is_invalid = true;
        
        for(int i = 1; i <= extra_bytes; i++){

            if(index+i >= str.size()){
                //return 0; for tests
                //throw runtime_error("Improperly formatted string. character incomplete, unable to read char and reached EOF\n");
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