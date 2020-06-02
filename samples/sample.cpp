#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
  FileManager file(argv[1]);
  file.info();
  auto out = file.list_files({".txt"});
  for(auto const& i: out) {
    std::cout << i.name << ", " << i.name << std::endl;
  }
  file.writeToFile(file, /*ignore_dirs=*/ {"build", ".git", ".github", ".vscode"});
}
