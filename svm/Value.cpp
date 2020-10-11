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

Value Value::operator+(Value right) {
    Value trt;
    if (type != right.type) {
        std::cout << "Error: Mismatched Types\n";
        exit(0);
    } else if (type == V_NUM) {
        trt.type = V_NUM;
        trt.dat = std::any_cast<int>(dat) + std::any_cast<int>(right.getRaw());
    } else if (type == V_STRING) {
        trt.type = V_STRING;
        trt.dat = std::any_cast<std::string>(dat) + std::any_cast<std::string>(right.getRaw());
    } else {
        std::cout << "Error: Unable to add types\n";
        exit(3);
    }
    return trt;
}

std::any Value::getRaw() {
  return dat;
}

