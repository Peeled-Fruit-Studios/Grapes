#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include "Program.h"
#include <stack>

namespace Grapes {
	class ExecutionEngine {
    public:
    ExecutionEngine(Grapes::Program tl) : ip(tl), counter(0), vcon(0) {}
    void run();
    private:
    int counter;
    int getInst();
    int vcon;
    Value getVal();
    std::stack<Value> ms;
    Grapes::Program ip;
	};
}
#endif
