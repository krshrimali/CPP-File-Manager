// FileManager class
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <cassert> // TODO: Replace all asserts with GTest framework
#include <fstream>

class FileManager {
  public:
    // Use it as FileManager::file_info
    struct file_info {
      std::string name;
      std::string rname;
      bool is_dir;
    };

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
    std::vector<std::string> list_files();
    std::vector<file_info> list_files_new();
    file_info make_file_info(std::string, std::string, bool);
    // TODO: pass by reference
    void writeToFile(FileManager, std::vector<std::string>);
    // TODO: pass by reference
    void writeToFileIterated(FileManager, std::ofstream&, int);
    bool dirTobeIgnored(std::string, std::vector<std::string>);
};
