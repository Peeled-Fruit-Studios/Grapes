#include "Program.h"
#include <iostream>

using namespace Grapes;

Program::Program() {
  counter = 0;
}

std::string dsi(int op) {
  switch(op) {
    case OP_RETURN:
    return "OP_RETURN";
    break;
    case OP_PRINT:
    return "OP_PRINT";
    break;
    case OP_LOAD:
    return "OP_LOAD";
    break;
    case OP_ADD:
    return "OP_ADD";
    break;
    case OP_SUBTRACT:
    return "OP_SUBTRACT";
    break;
    case OP_DIVIDE:
    return "OP_DIVIDE";
    break;
    case OP_MULTIPLY:
    return "OP_MULTIPLY";
    break;
  }
}

void Program::print() {
  std::cout << "Debugging Program...\n";
  std::cout << "-------------------------------\n";
  std::cout << "Operations...\n\n";
  for(int i = 0; i < ist.size(); i++) {
    std::cout << "Instruction: " << dsi(ist.at(i)) << std::endl;
  }
  std::cout << "-------------------------------\n";
  std::cout << "Values...\n\n";

  for (int b = 0; b < vals.size(); b++) {
    vals.at(b).print();
  }

  std::cout << "-------------------------------\n";

}