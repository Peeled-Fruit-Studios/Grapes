#ifndef PARSER_H
#define PARSER_H

#include <list>
#include "Scanner.h"

namespace Grapes {
  class Parser {
    public:
    Parser(std::string filename);
    void parse();
    private:
    void advance();
    void statement();
    void exp();
    void factor();
    void term();
    int offset;
    Grapes::Token curtok;
    std::list<Grapes::Token> toks;
  };
}

#endif