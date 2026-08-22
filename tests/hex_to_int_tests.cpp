
#include "check_valid_strings.h"
#include <iostream>

using namespace std;

int main(){

    //tests to see that hex properly converts into ints 

    cout<<"0 --> "<<hex_to_int('0')<<"\n";
    cout<<"1 --> "<<hex_to_int('1')<<"\n";
    cout<<"9 --> "<<hex_to_int('9')<<"\n";
    cout<<"a --> "<<hex_to_int('a')<<"\n";
    cout<<"f --> "<<hex_to_int('f')<<"\n";
    cout<<"A --> "<<hex_to_int('A')<<"\n";
    cout<<"F --> "<<hex_to_int('F')<<"\n";
    cout<<"g --> "<<hex_to_int('g')<<"\n";
    cout<<"G --> "<<hex_to_int('G')<<"\n";
    cout<<"/ --> "<<hex_to_int('/')<<"\n";
    cout<<": --> "<<hex_to_int(':')<<"\n";
    cout<<"@ --> "<<hex_to_int('@')<<"\n";
    cout<<"` --> "<<hex_to_int('`')<<"\n";
    cout<<"  --> "<<hex_to_int(' ')<<"\n";
    cout<<"~ --> "<<hex_to_int('~')<<"\n";

    cout<<"giving char c a int: \n";
    cout<<"int 0 --> "<<hex_to_int(0)<<"\n";
    cout<<"int 1 --> "<<hex_to_int(1)<<"\n";
    cout<<"int 9 --> "<<hex_to_int(9)<<"\n";
    cout<<"int 10 --> "<<hex_to_int(10)<<"\n";
    cout<<"int 15 --> "<<hex_to_int(15)<<"\n";
    cout<<"int 16 --> "<<hex_to_int(16)<<"\n";
    cout<<"int 32 --> "<<hex_to_int(32)<<"\n";
    cout<<"int 48 --> "<<hex_to_int(48)<<"\n";
    cout<<"int 57 --> "<<hex_to_int(57)<<"\n";
    cout<<"int 65 --> "<<hex_to_int(65)<<"\n";
    cout<<"int 70 --> "<<hex_to_int(70)<<"\n";
    cout<<"int 97 --> "<<hex_to_int(97)<<"\n";
    cout<<"int 102 --> "<<hex_to_int(102)<<"\n";
    cout<<"int 127 --> "<<hex_to_int(127)<<"\n";
    
    cout<<"see what happens if it overflows the char c capacity:\n";
    cout<<"int 128 --> "<<hex_to_int(128)<<"\n";
    cout<<"int 255 --> "<<hex_to_int(255)<<"\n";
    cout<<"int 256 --> "<<hex_to_int(256)<<"\n";
    cout<<"int -1 --> "<<hex_to_int(-1)<<"\n";
    cout<<"int -128 --> "<<hex_to_int(-128)<<"\n";
    cout<<"int -129 --> "<<hex_to_int(-129)<<"\n";

    cout<<"what if it wraps around to a valid char???\n";
    cout<<"int -130 --> "<<hex_to_int(-130)<<"\n";
    cout<<"int -127 --> "<<hex_to_int(-127)<<"\n";
    cout<<"int -64 --> "<<hex_to_int(-64)<<"\n";
    cout<<"int 257 --> "<<hex_to_int(257)<<"\n";
    cout<<"int 300 --> "<<hex_to_int(300)<<"\n";
    cout<<"int 511 --> "<<hex_to_int(511)<<"\n";
    cout<<"int 512 --> "<<hex_to_int(512)<<"\n";

    cout<<"testing hexadecimal boundaries:\n";
    cout<<"int 47 --> "<<hex_to_int(47)<<"\n";
    cout<<"int 58 --> "<<hex_to_int(58)<<"\n";
    cout<<"int 64 --> "<<hex_to_int(64)<<"\n";
    cout<<"int 71 --> "<<hex_to_int(71)<<"\n";
    cout<<"int 96 --> "<<hex_to_int(96)<<"\n";
    cout<<"int 103 --> "<<hex_to_int(103)<<"\n";


}