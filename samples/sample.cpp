#include "FileManager.hpp"

int main(){
    std::string path;
    std::cin >> path;
    FileManager fm = FileManager(path);
    std::cout << "Writing to tree.txt\n";
    fm.writeToFile();
    return 0;
}