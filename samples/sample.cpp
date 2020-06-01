#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
  FileManager file(argv[1]);
  file.info();
  file.writeToFile(file, /*ignore_dirs=*/ {"build", ".git", ".github", ".vscode"});
}
