#ifndef SCANNER_H
#define SCANNER_H

#include <any>
#include <iostream>
#include <list>

namespace Grapes {
  enum TokenType {
    LEFT_PAREN=5, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, LSTRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOFS, ERROR
  };
  class Token {
    public:
    Grapes::TokenType type;
    const char* start;
    int length;
    int line;
  };
  class Scanner {
    public:
    void setup(std::string filename);
    std::list<Token> ScanTokens();
    private:
    Token GetToken();
    int counter;
    int line;
  };
}

#endif