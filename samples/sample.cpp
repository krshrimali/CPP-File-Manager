#include <iostream>
#include "FileManager.hpp"

int main() {
    FileManager file(std::string("../../samples"));
    file.info();
    for (auto const& i: file.list_files()) {
        std::cout << i << std::endl;
    }
}