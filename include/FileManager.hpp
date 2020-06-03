// FileManager class
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <cassert>
#include <fstream>
#include <cstring>

class FileManager {
  // Fle Manager class
  // This class will help you handle files in the given path
  public:
    // Use it as FileManager::file_info
    struct file_info {
      std::string name;
      std::string rname;
      bool is_dir;
    };

    FileManager(std::string path) {
      // The whole class will potentially revolves around the subfolders inside the path (including the path)
      corePath = path;
    }
  
    void clear();
    void clear(std::string);
    void info();
    std::vector<file_info> list_files(std::vector<std::string> extensions = {}, bool ignore_extensions = false);
    // TODO: Why to pass FileManager object?
    void writeToFile(FileManager, std::vector<std::string> ignore_dirs = {}, std::vector<std::string> ignore_extensions = {});
  private:
    std::string corePath;
    // TODO: Why to pass FileManager object, and pass everything by reference!
    void writeToFileIterated(FileManager, std::ofstream&, int, std::vector<std::string>, std::vector<std::string>);
    bool itemInList(std::string, std::vector<std::string>);
    file_info make_file_info(std::string, std::string, bool);
};
