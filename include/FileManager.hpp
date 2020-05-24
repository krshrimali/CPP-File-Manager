// FileManager class
#include <iostream>
#include <string>

class FileManager {
  public:
    // Fle Manager class
    // This class will help you handle files in the given path
    std::string corePath;

    FileManager(std::string path) {
      // The whole class will potentially revolve around the subfolders inside the path (including the path)
      corePath = path;
    }
  
    void clear();
    void clear(std::string);
    void info();
};