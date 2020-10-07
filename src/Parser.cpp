#include "Parser.h"
#include <iostream>
#include <cstdlib>

using namespace Grapes;

Parser::Parser(std::string filename) {
  Scanner sc;
  sc.setup(filename);
  toks = sc.ScanTokens();
  offset = 0;
  advance();
}

void Parser::parse() {
  statement();
}

void Parser::advance() {
  auto curto = std::next(toks.begin(), offset++);
  curtok = *curto;
}

void Parser::statement() {
  if (curtok.type == PRINT) {
    advance();
    exp();
    std::cout << "PRINT\n";
    advance();
  } else {
    std::cout << "Error: Unexpected Start of Program\n";
  }
}

void Parser::exp() {
  term();
  while(curtok.type == PLUS || curtok.type == MINUS) {
    if(curtok.type == PLUS) {
      advance();
      term();
      std::cout << "ADD\n";
    } else {
      advance();
      term();
      std::cout << "MINUS\n";
    }
  }
}

void Parser::term() {
  factor();
  while(curtok.type == SLASH || curtok.type == STAR) {
    if(curtok.type == SLASH) {
      advance();
      factor();
      std::cout << "DIVIDE\n";
    } else {
      advance();
      factor();
      std::cout << "MULTIPLY\n";
    }
  }
}

void Parser::factor() {
  if(curtok.type == NUMBER) {
    std::string hl = curtok.start;
    int res = std::atoi(hl.substr(0, curtok.length).c_str());
    std::cout << "LOADING NUMBER " << res << std::endl;
    advance();
  }
}