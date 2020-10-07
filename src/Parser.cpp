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

void Parser::storeValue(Value v) {
  tdump.vals.push_back(v);
  tdump.ist.push_back(OP_LOAD);
}

void Parser::emitOP(int op) {
  tdump.ist.push_back(op);
}

Program Parser::parse() {
  statement();
  emitOP(OP_RETURN);
  return tdump;
}

void Parser::advance() {
  auto curto = std::next(toks.begin(), offset++);
  curtok = *curto;
}

void Parser::statement() {
  if (curtok.type == PRINT) {
    advance();
    exp(SEMICOLON);
    emitOP(OP_PRINT);
    advance();
  } else {
    error("Invalid Start of Program");
  }
}

void Parser::exp(TokenType t) {
  if (curtok.type == t) {
    return;
  }
  term();
  while(curtok.type == PLUS || curtok.type == MINUS) {
    if(curtok.type == PLUS) {
      advance();
      term();
      emitOP(OP_ADD);
    } else {
      advance();
      term();
      emitOP(OP_SUBTRACT);
    }
  }
}

void Parser::term() {
  factor();
  while(curtok.type == SLASH || curtok.type == STAR) {
    if(curtok.type == SLASH) {
      advance();
      factor();
      emitOP(OP_DIVIDE);
    } else {
      advance();
      factor();
      emitOP(OP_MULTIPLY);
    }
  }
}

void Parser::error(std::string info) {
  std::cout << "Error [line " << curtok.line << "]: " << info << std::endl;
  exit(3);
}

void Parser::factor() {
  if(curtok.type == NUMBER) {
    std::string hl = curtok.start;
    int res = std::atoi(hl.substr(0, curtok.length).c_str());
    storeValue(Value(V_NUM, res));
    advance();
  } else if(curtok.type == LEFT_PAREN) {
    advance();
    exp(RIGHT_PAREN);
    advance();
  } else if (curtok.type == ERROR) {
    std::string hl = curtok.start;
    error(hl.substr(0, curtok.length));
  } else if (curtok.type == LSTRING) {
    std::string hl = curtok.start;
    storeValue(Value(V_STRING, hl.substr(1, curtok.length - 2)));
  } else {
    error("Invalid Expression");
  }
}