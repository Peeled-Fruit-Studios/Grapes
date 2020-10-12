#include <iostream>
#include <fstream>
#include <cstring>

void usage() {
  std::cout << "Usage: ClassGen < SVM | Grapes> <Name of class>\n";
  exit(0);
}

std::string filoc;
std::string hloc;

int main(int argc, char *argv[]) {
  if(argc < 3) {
    usage();
  }
  std::string classname = argv[2];
  if(memcmp(argv[1], "SVM", 3) == 0) {
    filoc = "svm/";
    hloc = "svm/include/";
  } else if (memcmp(argv[1], "Grapes", 6) == 0) {
    filoc = "src/";
    hloc = "include/";
  } else {
    std::cout << "Error: Mode not Specified\n";
    exit(0);
  }
  std::cout << "Generating class " << classname << std::endl;
  std::ofstream cpf(filoc + classname + ".cpp");
  cpf << "#include \"" << classname << ".h\"" << "\n\n\n";
  cpf.close();
  std::ofstream hpf(hloc + classname + ".h");
  hpf << "#ifndef " + classname + "_H\n";
  hpf << "#define " + classname + "_H\n\n";
  hpf << "namespace Grapes {\n";
  hpf << "\tclass " << classname << " {\n\t\n\t};\n";
  hpf << "}\n";
  hpf << "#endif\n";
  hpf.close();
  std::cout << "Done Generating class " << classname << std::endl;
} 