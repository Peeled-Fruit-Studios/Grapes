#include "NScanner.h"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace Grapes;
using namespace std;

static Location* sloc;
static int pos;

NScanner(char* filename) {
  curloc.filename = filename;
  curloc.line = 1;

  sloc = &curloc;

  pos = 0;

  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  data = buffer.str();
  t.close();
  buffer.str(std::string());
}

NToken mkToken(int type, std::string fname) {
  NToken nj;
  nj.lj = *sloc;
  nj.type = type;
  nj.rval = fname;
}

static void skipTrash() {
  char g = data.at(pos);
  while(g == '\n' || g == '\r' || g == '\t') {
    if (g == '\n') {
      sloc.line++;
    }
    g = data.at(++pos);
  }
}

NToken scanTok() {
  skipTrash();
  char cj = data.at(pos);
  if(cj == '\0') {
    return mkToken(EOF, "");
  }
  switch (cj) {
    case '(': return mkToken(LEFT_PAREN, ""); break;
    case ')': return mkToken(RIGHT_PAREN, ""); break;
    case '{': return mkToken(LEFT_BRACE, ""); break;
    case '}': return mkToken(RIGHT_BRACE, ""); break;
    case ',': return mkToken(COMMA, ""); break;
    case '.': return mkToken(DOT, ""); break;
    case '-': return mkToken(MINUS, ""); break;
    case '+': return mkToken(PLUS, ""); break;
    case ';': return mkToken(SEMICOLON, ""); break;
    case '*': return mkToken(STAR, ""); break; 
  }
}

list<NToken> lex() {

}