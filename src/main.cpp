#include <iostream>
#include <cstring>
#include "GrapesConf.h"
#include "ExecutionEngine.h"
#include "Program.h"
#include "Value.h"
#include "Parser.h"

void preamble() {
  std::cout << "Grapes v" << GRAPES_VERSION_MAJOR << "." << GRAPES_VERSION_MINOR << ", Copyright 2020 Peeled Fruit Studios. All Rights Reserved.\n";

  #ifdef BUILD_INSTALLER
  std::cout << "Built from installer: Yes\n";
  #endif
  #ifndef BUILD_INSTALLER
  std::cout << "Built from installer: No\n";
  #endif

  std::cout << "Operating System: " << CMAKE_SYSTEM << std::endl;

  std::cout << "CPU Arch: " << CMAKE_SYSTEM_PROCESSOR << std::endl;
}

/*std::cout << "Testing Complete Scanner\n";
  std::list<Grapes::Token> gh;
  gh  = sc.ScanTokens();

  for(int i = 0; i < gh.size(); i++) {
    auto item = std::next(gh.begin(), i);
    if(item->type == EOF) {
      return 0;
    } else if((int)item->type == 25) {
      std::string hl = item->start;
      std::cout << hl.substr(1, item->length - 2) << " | " << item->line << std::endl;
    } else {
      std::string hl = item->start;
      std::cout << hl.substr(0, item->length) << " | " << item->line << std::endl;
    }
  } */

int main(int argc, char* argv[]) {

  if(argc != 2) {
      std::cout << "Error: Incorrect Number of Arguments Specified\n";
      exit(3);
  }

  if (memcmp(argv[1], "about", 5) == 0) {
      preamble();
      exit(0);
  }

  Grapes::Parser ps(argv[1]);

  Grapes::Program pt = ps.parse();

  Grapes::ExecutionEngine rt(pt);

  rt.run();
  
}
