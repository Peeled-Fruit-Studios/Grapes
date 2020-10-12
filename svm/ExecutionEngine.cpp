#include "ExecutionEngine.h"

using namespace Grapes;

int ExecutionEngine::getInst() {
  if (counter > ip.ist.size()) {
    exit(0);
  } else {
    return ip.ist.at(counter++);
  }
}

void rtError(std::string message) {
  std::cout << "Error: (Runtime) " << message << std::endl;
  exit(0);
}

Value ExecutionEngine::getVal() {
  if (vcon > ip.vals.size()) {
    rtError("Attemting to reach void memory");
  } else {
    return ip.vals.at(vcon++);
  }
}

void ExecutionEngine::run() {
  Value hg;
  for(;;) {
    switch(getInst()) {
      case OP_LOAD:
      ms.push(getVal());
      break;
      case OP_PRINT:
      ms.top().print();
      ms.pop();
      break;
      case OP_RETURN:
      exit(0);
      break;
    }
  }
}