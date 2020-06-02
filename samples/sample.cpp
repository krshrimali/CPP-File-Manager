#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
  FileManager file(argv[1]);
  file.info();
  auto out = file.list_files({".jpg", ".png"});
  for(auto const& item: out) {
    std::cout << item.name << std::endl;
  }
  file.writeToFile(file, /*ignore_dirs=*/ {"build", ".git", ".github", ".vscode"});
}
