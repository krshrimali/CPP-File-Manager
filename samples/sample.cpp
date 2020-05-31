#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
    FileManager file(argv[1]);
    file.info();
    /* file.list_files_new() ;
    for (auto const& i: file.list_files_new()) {
        std::cout << i.name << std::endl;
        std::cout << "is_dir: " << i.is_dir << std::endl ;
    } */
    file.writeToFile(file, /*ignore_dirs=*/ {"build", ".git"});
}
