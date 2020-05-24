#include <iostream>
// TODO: Add include path to CMakeLists.txt of samples/ dir
#include "../include/FileManager.hpp"

int main() {
    FileManager file(std::string("Kush/"));
    file.info();
}
