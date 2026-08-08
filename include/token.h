#ifndef TOKEN_H
#define TOKEN_H

#include "position.h"

#include <vector>
#include <map>
#include <ostream>

enum TokenType {
    EMPTY, //testing purposes. this is the default value for tokentype
    LBRACE, RBRACE,
    LBRAKET, RBRAKET,
    STRING,
    NULL_T, FALSE_T, TRUE_T, //t = terminal? token?
    COMMA, COLON, 
    NUMBER,
    END_OF_FILE
};

inline const std::map<TokenType, std::string>printable_tokentype{
    {EMPTY, "EMPTY"},
    {LBRACE, "LBRACE"},
    {RBRACE, "RBRACE"},
    {LBRAKET, "LBRAKET"},
    {RBRAKET, "RBRAKET"},
    {STRING, "STRING"},
    {NULL_T, "NULL_T"},
    {FALSE_T, "FALSE_T"},
    {TRUE_T, "TRUE_T"},
    {COMMA, "COMMA"},
    {COLON, "COLON"},
    {NUMBER, "NUMBER"},
    {END_OF_FILE, "END_OF_FILE"}
    
};

struct Token{
    TokenType type;
    std::vector<char> lexeme {};
    Position location{};
    //int len;

    //Token() = delete;
    Token() = default;

    Token(char c, TokenType t, Position p){
        lexeme.push_back(c);
        type = t;
        location = {p};
    }
    //--------------------------------
    Token(std::vector<char> v, TokenType t, Position p) : lexeme{v}, type{t}, location{p} /*, len{(int)(v.size())}*/ {}

    friend std::ostream& operator<<(std::ostream& os, const Token& t){
       return os << (printable_tokentype.at(t.type) + "(" + std::string(t.lexeme.begin(), t.lexeme.end()) + ")");
      
    };

};

#endif