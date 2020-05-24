#include "FileManager.hpp"

void FileManager::clear() {
  std::cout << "Deleting file manager...\n";
  corePath.clear();
}

void FileManager::clear(std::string newPath) {
  std::cout << "Clearing file manager with new path\n";
  corePath = newPath;
}

void FileManager::info() {
  std::cout << "Current path: " << corePath << std::endl;
}