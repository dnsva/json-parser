
#include <iostream>
#include <filesystem> //cpp17 - use this for reading from json and converting to str_view
#include <fstream>
#include <optional>
#include <cctype>

#include <string_view>
#include "token.h"
#include "position.h"

namespace fs = std::filesystem;
using namespace std;

Position curr_pos{0};
int file_index = 0;
string_view file = "";

char peek(){
    if(file_index + 1 < file.size()) return file[file_index+1];
    return '\0';
}

char get(){
    if(file_index + 1 < file.size()){
        curr_pos++;
        return file[++file_index];
    }
    return '\0';
}

optional<Token> get_terminal(char c){ //std::optional is cpp17 - also contextually converts into bool
    //terminals: { } ( ) , ; "

    Token t;
    if(c == '{') t = Token{'{', LBRACE, curr_pos};
    else if(c == '}') t = Token{'}', RBRACE, curr_pos};
    else if(c == '[') t = Token{'[', LBRAKET, curr_pos};
    else if(c == ']') t = Token{']', RBRAKET, curr_pos};
    else if(c == ',') t = Token{',', COMMA, curr_pos};
    else if(c == ':') t = Token{':', COLON, curr_pos};
    else return {}; //return false

    return t;

}

optional<Token> get_literal(char c){

    vector<char> null_literal = {'n', 'u', 'l', 'l'};
    vector<char> true_literal = {'t', 'r', 'u', 'e'};
    vector<char> false_literal = {'f', 'a', 'l', 's', 'e'};

    int counter = 1; //0 is already counted since first char is passed in
    if (c == 'n'){
        while(counter < 4 && peek() == null_literal[counter]){
            counter++;
            get();
        }
        if(counter == 4) return Token{null_literal, NULL_T, curr_pos};
        return {};
    }

    if (c == 't'){
        // reset counter for this branch
        counter = 1;
        while(counter < 4 && peek() == true_literal[counter]){
            counter++;
            get();
        }
        if(counter == 4) return Token{true_literal, TRUE_T, curr_pos};
        return {};
    }

    if (c == 'f'){
        // reset counter for this branch
        counter = 1;
        while(counter < 5 && peek() == false_literal[counter]){
            counter++;
            get();
        }
        if(counter == 5) return Token{false_literal, FALSE_T, curr_pos};
        return {};
    }
    return {}; //invalid
}

Token next_token(){

   // curr_pos++;
   // file_index++;

    char curr_char = file[file_index];

    //check for and eat whitespace
    while(curr_char == '\n' || curr_char == ' ' || curr_char == '\t' || curr_char == '\r'){
        if(curr_char == '\n'){ curr_pos.row++; curr_pos.col = 0; }
        else { curr_pos.col++; }
        file_index++;
        curr_char = file[file_index];
    }

    if(curr_char == '\0') return {'\0', END_OF_FILE, curr_pos};

    //terminal:
    auto t = get_terminal(curr_char);

    if (t.has_value()) {
        curr_pos++;
        file_index++;
        return t.value();
    }

    //non-terminal:
        //number
        //string
        //null, false, true

    //number
    if(isdigit(curr_char)){
        //must be a number...

        vector<char> digit {curr_char};

        while(isdigit(peek()) || peek() == 'e' || peek() == 'E' || peek() == '+' || peek() == '-' || peek() == '.'){
            digit.push_back(get());
        }

        t = {digit, NUMBER, curr_pos};

        curr_pos++;
        file_index++;
        return t.value();
    }

    //string
    if(curr_char == '"'){
        //must be a string
        vector<char>str {'"'};
        while(peek() != '"' && peek() != '\0'){ //end quote
            str.push_back(get());
        }
        
        str.push_back(get()); //should be the end ". if not:
        if(str[file_index] != '"'){
            throw runtime_error("no \" found to end string\n");
        }

        t = {str, STRING, curr_pos};

        curr_pos++;
        file_index++;
        return t.value();
    }

    //true false or null
    t = get_literal(curr_char);
    if(!t.has_value()){
        throw runtime_error("BAD\n");
        //return;
    }

    curr_pos++; //for next token
    file_index++; //for next token
    return t.value();

}


/*

int main(){

    fs::path json_file_path = {"test.json"};

    write json contents into json_string 
    ifstream json_file(json_file_path, ios::in | ios::binary); //double check if binary is needed
    const auto size_of_file = fs::file_size(json_file_path);
    string json_string(size_of_file, '\0');
    json_file.read(json_string.data(), size_of_file);


    cout<<json_string<<"\n";

    string_view json_strview {json_string};

    cout<<json_strview<<"\n";
    
    //now there is a string with the contents of the file!

}



whitespace regex
ws = "[\n\r\t ]";
newline = "\r\n|\n|\r";

*/