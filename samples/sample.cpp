#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
  FileManager file(argv[1]);
  file.info();
  auto out = file.list_files({".pyc", ".txt", ".wav"}, /*ignore_extensions=*/ true);
  for(auto const& item: out) {
    std::cout << item.name << std::endl;
  }
  file.writeToFile(file, /*ignore_folders=*/ {".git"}, /*ignore_extensions=*/ {".txt", ".pyc"});
}
