#include "Value.h"

using namespace Grapes;

void Value::print() {
  switch(type) {
    case V_NUM:
    std::cout << std::any_cast<int>(dat) << std::endl;
    break;
    case V_STRING:
    std::cout << std::any_cast<std::string>(dat) << std::endl;
    break;
    case V_NULL:
    std::cout << "null\n";
    break;
    case V_BOOL:
    std::cout << std::any_cast<bool>(dat) << std::endl;
    break;
  }
}

std::any Value::getRaw() {
  return dat;
}