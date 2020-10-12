//
// Created by Uiop on 10/10/2020.
//

#include "ExecutionEngine.h"
#include <iostream>

using namespace Grapes;

ExecutionEngine::ExecutionEngine(Grapes::Program tp) {
    ip = tp;
    counter = 0;
    vcon = 0;
}

int ExecutionEngine::getInst() {
    if(counter > ip.ist.size()) {
        exit(0);
    } else {
        return ip.ist.at(counter++);
    }
}

void rtError(const std::string message) {
    std::cout << "Error: (Runtime) " << message << std::endl;
    exit(3);
}

Value ExecutionEngine::getConst() {
    if(vcon > ip.vals.size()) {
        rtError("Attempting to reach non-existent memory");
    } else {
        return ip.vals.at(vcon++);
    }
}

Value subVal(Value left, Value right) {
    Value toret;
    toret.type = V_NUM;
    if (left.type != V_NUM || left.type != right.type) {
        rtError("Can't subtract something that isn't num");
    } else {
        toret.setRaw(std::any_cast<int>(left.getRaw()) - std::any_cast<int>(right.getRaw()));
    }
    return toret;
}

Value mulVal(Value left, Value right) {
    Value toret;
    toret.type = V_NUM;
    if (left.type != V_NUM || left.type != right.type) {
        rtError("Can't subtract something that isn't num");
    } else {
        toret.setRaw(std::any_cast<int>(left.getRaw()) * std::any_cast<int>(right.getRaw()));
    }
    return toret;
}

Value divVal(Value left, Value right) {
    Value toret;
    toret.type = V_NUM;
    if (left.type != V_NUM || left.type != right.type) {
        rtError("Can't subtract something that isn't num");
    } else {
        toret.setRaw(std::any_cast<int>(left.getRaw()) / std::any_cast<int>(right.getRaw()));
    }
    return toret;
}

void ExecutionEngine::run() {
    // Used as a holder for arithmetic operations
    Value vls[2];
    for(;;) {
        switch(getInst()) {
            case OP_PRINT:
                ms.top().print();
                ms.pop();
                break;
            case OP_LOAD:
                ms.push(getConst());
                break;
            case OP_ADD:
                vls[0] = ms.top();
                ms.pop();
                vls[1] = ms.top();
                ms.pop();
                ms.push(vls[0] + vls[1]);
                break;
            case OP_SUBTRACT:
                vls[0] = ms.top();
                ms.pop();
                vls[1] = ms.top();
                ms.pop();
                ms.push(subVal(vls[0], vls[1]));
                break;
            case OP_MULTIPLY:
                vls[0] = ms.top();
                ms.pop();
                vls[1] = ms.top();
                ms.pop();
                ms.push(mulVal(vls[0], vls[1]));
                break;
            case OP_RETURN:
                exit(0);
                break;
            case OP_DIVIDE:
                vls[0] = ms.top();
                ms.pop();
                vls[1] = ms.top();
                ms.pop();
                ms.push(divVal(vls[0], vls[1]));
                break;
        }
    }
}