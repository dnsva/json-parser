
#include <iostream>
#include <filesystem> //cpp17 - use this for reading from json and converting to str_view
#include <fstream>
#include <optional>
#include <cctype>
#include <vector>
#include <string_view>
#include "token.h"
#include "position.h"

namespace fs = std::filesystem;
using namespace std;

/* Global variables */
Position curr_pos{0};
int file_index = 0;
string_view file_str_view = "";

/* View next character without updating current position */
char peek_next(){
    if(file_index + 1 < file_str_view.size()) return file_str_view[file_index+1];
    return '\0';
}

/* Get next character and update position */
char get_next(){
    if(file_index + 1 < file_str_view.size()){
        curr_pos++;
        return file_str_view[++file_index];
    }
    return '\0';
}

/*
Return a token if the CURRENT char is a terminal character ({ } [ ] , ; "). false/empty otherise 
--> current position stays at last consumed char.
*/
optional<Token> get_terminal(char c){

    if(c == '{')      return Token{'{', LBRACE, curr_pos};
    else if(c == '}') return Token{'}', RBRACE, curr_pos};
    else if(c == '[') return Token{'[', LBRAKET, curr_pos};
    else if(c == ']') return Token{']', RBRAKET, curr_pos};
    else if(c == ',') return Token{',', COMMA, curr_pos};
    else if(c == ':') return Token{':', COLON, curr_pos};
    else              return {}; //return false

}

/*
Return a token if the curr char is the beginning of a number.
--> curr position stays at the last consumed char
*/
optional<Token> get_number(char c){

    Position start_pos = curr_pos;

    if(isdigit(c) || c == '-'){

        vector<char> digit {c};

        while(isdigit(peek_next()) || peek_next() == 'e' || peek_next() == 'E' || peek_next() == '+' || peek_next() == '-' || peek_next() == '.'){
            digit.push_back(get_next());

            if(digit.back() == '-' &&  !isdigit(peek_next())){ //check: something about isdigit not working on - char values
                cout<<"the char found after - is "<<peek_next()<<"\n";
                throw runtime_error("Must have digit after a - \n");
            }
        }

        if(digit.back() == '-'){ //take care of the case if just - is passed in
            throw runtime_error("Must have a digit after a - \n");
        }

        return Token{digit, NUMBER, start_pos};
    }
    return {};
}

/*
Return a token if the curr char is the beginning of a string
--> curr position stays at thte last consumed char
*/
optional<Token> get_string(char c){

    Position start_pos = curr_pos;

    if(c == '"'){
        //must be a string
        vector<char>str {'"'};

        while(peek_next() != '"' && peek_next() != '\0'){
            str.push_back(get_next());
            //if(str.back() == '\\' && peek_next() == '"') str.push_back(get_next());
            if(str.back() == '\\') str.push_back(get_next());  //consume the escapee
        }

        if(peek_next() == '"'){
            str.push_back(get_next());
        }else{
            throw runtime_error("no \" found to end string\n");
        }

        return Token{str, STRING, start_pos};
    }
    return {};
}

/* 
Return a literal token (null, true, false) if the curr char is the beginning of one. false/empty otherise.
--> current position stays at last consumed char.
*/
optional<Token> get_literal(char c){

    Position start_pos = curr_pos;

    vector<char> null_literal = {'n', 'u', 'l', 'l'};
    vector<char> true_literal = {'t', 'r', 'u', 'e'};
    vector<char> false_literal = {'f', 'a', 'l', 's', 'e'};

    if (c == 'n'){
        int i;
        for(i = 1; i < 4 && peek_next() == null_literal[i]; i++)
            get_next();
        if(i == 4)
            return Token{null_literal, NULL_T, start_pos};
        
    }else if (c == 't'){
        int i;
        for(i = 1; i < 4 && peek_next() == true_literal[i]; i++)
            get_next();
        if(i == 4)
            return Token{true_literal, TRUE_T, start_pos};
       
    }else if (c == 'f'){
        int i;
        for(i = 1; i < 5 && peek_next() == false_literal[i]; i++)
            get_next();
        if(i == 5)
            return Token{false_literal, FALSE_T, start_pos};
    }else{
        return {}; //not a literal at all
    }

    throw std::runtime_error("BAD literal\n"); //if didnt fully go thru literal check loops
}

/*
Gets the next token starting at current char
--> current position stays at last consumed char of the full token
*/
Token get_token(){

    if(file_index >= file_str_view.size()){ //check if EOF error
        throw std::runtime_error("Accessing beyond file size\n"); //EOF should have been checked outside this fn
    }

    char curr_char = file_str_view[file_index];

    //check for and eat whitespace
    while(curr_char == '\n' || curr_char == ' ' || curr_char == '\t' || curr_char == '\r'){

        if(curr_char == '\n'){
            curr_pos.row++;
            curr_pos.col = 0; 
        }else{
            curr_pos++; //updates the column
        }

        file_index++;
        curr_char = file_str_view[file_index];
    }

    /*
    TRY:
        1) terminal characters
        2) numbers
        3) strings
        4) literals: null, false, true
    */

    //(1) terminal characters:
    auto t = get_terminal(curr_char);
    if (t.has_value()) return t.value();

    //(2) numbers
    t = get_number(curr_char);
    if(t.has_value()) return t.value();
    
    //(3) strings
    t = get_string(curr_char);
    if(t.has_value()) return t.value();

    //(4) literals
    t = get_literal(curr_char);
    if(t.has_value()) return t.value();

    //If none of the tokens worked:
    throw std::runtime_error("INVALID TOKEN\n");
    //return {};
}

vector<Token> get_token_stream(string_view& s){

    file_str_view = s; //set global file_str_view variable

    vector<Token> tokenstream{};

    while(file_index < file_str_view.size()){ //This does the EOF check

        tokenstream.push_back(get_token());

        //Very important: 
        curr_pos++;   //for next token
        file_index++; //for next token

    }

    tokenstream.push_back({'\0', END_OF_FILE, curr_pos});

    return tokenstream;
}


/* MAIN IS FOR TESTING */
int main(){

    fs::path json_file_path = {"test.json"};

    //write json contents into json_string 
    ifstream json_file(json_file_path, ios::in | ios::binary); //double check if binary is needed
    const auto size_of_file = fs::file_size(json_file_path);
    string json_string(size_of_file, '\0');
    json_file.read(json_string.data(), size_of_file);


    //cout<<json_string<<"\n";

    string_view json_strview {json_string};

    cout<<json_strview<<"\n";

    vector<Token> tokenstream = get_token_stream(json_strview);

    cout<<"----------------------------------------------------\n";
    cout<<"(R, C)\t|\tToken\n";
    cout<<"----------------------------------------------------\n";
    for(auto t:tokenstream){
        cout<<"("<<t.location.row<<","<<t.location.col<<")\t|\t";
        cout<<t<<"\n";
    }
    cout<<"\n";
}

/*

whitespace regex
ws = "[\n\r\t ]";
newline = "\r\n|\n|\r";

*/