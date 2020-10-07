#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <any>

#define V_NUM 54
#define V_STRING 87
#define V_NULL 25
#define V_BOOL 12

namespace Grapes {
  class Value {
    public:
    int type;
    Value(int typ, std::any gh) : dat(gh), type(typ){}
    void print();
    std::any getRaw();
    private:
    std::any dat;
  };
}

#endif