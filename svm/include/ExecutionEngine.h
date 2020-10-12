//
// Created by Uiop on 10/10/2020.
//

#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include "Program.h"
#include "Value.h"
#include <stack>

namespace Grapes {
    class ExecutionEngine {
    public:
        ExecutionEngine(Grapes::Program tp);
        void run();
    private:
        std::stack<Value> ms;
        Grapes::Program ip;
        int counter;
        int vcon;
        Value getConst();
        int getInst();
    };
}


#endif //EXECUTIONENGINE_H
