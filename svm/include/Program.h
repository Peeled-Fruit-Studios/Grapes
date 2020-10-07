#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include "Value.h"

#define OP_RETURN 91
#define OP_PRINT 34
#define OP_ADD 75
#define OP_LOAD 45
#define OP_SUBTRACT 63
#define OP_DIVIDE 23
#define OP_MULTIPLY 87

namespace Grapes {
  class Program {
    public:
    std::vector<Value> vals;
    std::vector<int> ist;
    Program();
    void print();
    Value getVal();
    private:
    int counter;
  };
}

#endif