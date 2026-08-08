#ifndef TOKEN_H
#define TOKEN_H

#include "position.h"

#include <vector>
#include <map>

enum TokenType {
    LBRACE, RBRACE,
    LBRAKET, RBRAKET,
    STRING,
    NULL_T, FALSE_T, TRUE_T, //t = terminal? token?
    COMMA, COLON, 
    NUMBER,
    END_OF_FILE
};

struct Token{
    TokenType type;
    vector<char> lexeme {};
    Position location{};
    int len{};

    //Token() = delete;
    Token();

    Token(char c, Position p){
        lexeme.push_back(c);
        if(!location.exists) location = {p};
    }
    Token(char c, TokenType t, Position p){
        lexeme.push_back(c);
        type = t;
        location = {p};
    }
    //--------------------------------
    Token(vector<char> v, TokenType t, Position p) : lexeme{v}, TokenType{t}, location{p}, len{v.size()};
    //--------------------------------
    /*Token(string_view s, Position p){
        lexeme = {s.begin(), s.end()};
        location = {p};
    }*/

};

#endif