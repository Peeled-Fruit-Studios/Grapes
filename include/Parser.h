#ifndef PARSER_H
#define PARSER_H

#include <list>
#include "Scanner.h"
#include "Program.h"

namespace Grapes {
  class Parser {
    public:
    Parser(std::string filename);
    Grapes::Program parse();
    private:
    void error(std::string info);
    void advance();
    void statement();
    void exp(Grapes::TokenType t);
    void factor();
    void term();
    void emitOP(int op);
    void storeValue(Value v);
    int offset;
    Grapes::Token curtok;
    Grapes::Program tdump;
    std::list<Grapes::Token> toks;
  };
}

#endif