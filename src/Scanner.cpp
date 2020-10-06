#include "Scanner.h"
#include <cstdio>
#include <cstring>

using namespace std;
using namespace Grapes;

int line;

typedef struct {
  const char* start;
  const char* current;
  int line;
} Lexer;

Lexer nkg;

void trim(Token* nk) {
  std::string ba = nk->start;
  std::string ee = ba.substr(0, nk->length);
  nk->start = (char*)ee.c_str();
}

extern "C" char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  if (!file)
    printf("Error: Unable To Open File %s\n", path);

  fseek(file, 1, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 2);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

void Scanner::setup(std::string filename) {
  const char* data = readFile(filename.c_str());
  nkg.start = data;
  nkg.current = data;
  nkg.line = 1;
}

static char advance() {
  nkg.current++;
  return nkg.current[-1];
}

static bool isAtEnd() {
  return *nkg.current == '\0';
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = nkg.start;
  token.length = (int)(nkg.current - nkg.start);
  token.line = nkg.line;

  return token;
}


static Token errorToken(const char* message) {
  Token token;
  token.type = ERROR;
  token.start = message;
  token.length = 21;
  token.line = nkg.line;

  return token;
}

bool match(char expected) {
  if (isAtEnd()) return false;
  if (*nkg.current != expected) return false;

  nkg.current++;
  return true;
}

static char peek() {
  return *nkg.current;
}

static char peekNext() {
  if (isAtEnd()) return '\0';
  return nkg.current[1];
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\n':
        nkg.line++;
        advance();
        break;
      case '\t':
        advance();
        break;

      case '/':
        if (peekNext() == '/') {
          // A comment goes until the end of the line.
          while (peek() != '\n' && !isAtEnd()) advance();
        } else {
          return;
        }
        break;

      default:
        return;
    }
  }
}

static Token stri() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') nkg.line++;
    advance();
  }

  if (isAtEnd()) return errorToken("Unterminated string.");

  // The closing quote.
  advance();
  return makeToken(LSTRING);
}

static bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

static Token number() {
  while (isDigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the ".".
    advance();

    while (isDigit(peek())) advance();
  }

  return makeToken(NUMBER);
}

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

static TokenType checkKeyword(int start, int length,
    const char* rest, TokenType type) {
  if (nkg.current - nkg.start == start + length &&
      memcmp(nkg.start + start, rest, length) == 0) {
    return type;
  }

  return IDENTIFIER;
}

static TokenType identifierType()
{
  switch (nkg.start[0]) {
    case 'a': return checkKeyword(1, 2, "nd", AND);
    case 'c': return checkKeyword(1, 4, "lass", CLASS);
    case 'e': return checkKeyword(1, 3, "lse", ELSE);
    case 'f':
      if (nkg.current - nkg.start > 1) {
        switch (nkg.start[1]) {
          case 'a': return checkKeyword(2, 3, "lse", FALSE);
          case 'o': return checkKeyword(2, 1, "r", FOR);
          case 'u': return checkKeyword(2, 1, "n", FUN);
        }
      }
      break;
    case 'i': return checkKeyword(1, 1, "f", IF);
    case 'n': return checkKeyword(1, 2, "il", NIL);
    case 'o': return checkKeyword(1, 1, "r", OR);
    case 'p': return checkKeyword(1, 4, "rint", PRINT);
    case 'r': return checkKeyword(1, 5, "eturn", RETURN);
    case 's': return checkKeyword(1, 4, "uper", SUPER);
    case 't':
      if (nkg.current - nkg.start > 1) {
        switch (nkg.start[1]) {
          case 'h': return checkKeyword(2, 2, "is", THIS);
          case 'r': return checkKeyword(2, 2, "ue", TRUE);
        }
      }
      break;
    case 'v': return checkKeyword(1, 2, "ar", VAR);
    case 'w': return checkKeyword(1, 4, "hile", WHILE);
  }

  return IDENTIFIER;
}


static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek())) advance();

  return makeToken(identifierType());
}

Token Scanner::GetToken() {
  skipWhitespace();

  nkg.start = nkg.current;

  if (isAtEnd()) return makeToken(EOFS);

  char c = advance();

  if (isAlpha(c)) return identifier();
  if (isDigit(c)) return number();
  //named function stri because string is reserved
  if (c == '"') return stri();

  switch (c) {
    case '(': return makeToken(LEFT_PAREN);
    case ')': return makeToken(RIGHT_PAREN);
    case '{': return makeToken(LEFT_BRACE);
    case '}': return makeToken(RIGHT_BRACE);
    case ';': return makeToken(SEMICOLON);
    case ',': return makeToken(COMMA);
    case '.': return makeToken(DOT);
    case '-': return makeToken(MINUS);
    case '+': return makeToken(PLUS);
    case '/': return makeToken(SLASH);
    case '*': return makeToken(STAR);
    case '!':
      return makeToken(match('=') ? BANG_EQUAL : BANG);
    case '=':
      return makeToken(match('=') ? EQUAL_EQUAL : EQUAL);
    case '<':
      return makeToken(match('=') ? LESS_EQUAL : LESS);
    case '>':
      return makeToken(match('=') ?
                       GREATER_EQUAL : GREATER);
  }

  return errorToken("Unexpected character.");
}

std::list<Token> Scanner::ScanTokens() {
  Token hld = GetToken();
  std::list<Token> trt;
  while(hld.type != EOFS) {
    trt.push_back(hld);
    hld = GetToken();
  }
  return trt;
}