// FileManager class
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<iterator>
#include<boost/filesystem.hpp>

class FileManager {
  // FileManager Class
  // Public Methods:
  // 1. clear(): clears the memory allocated for folder path (a.k.a corePath)
  // 2. clear(string): replaces the core path with the given path
  // 3. info(): Prints the core path to the console.
  // 4. list_files(vector<string> extensions, bool ignore_extensions): Use this to list files in the path given while creating the constructor. Pass extensions and ignore_extensions as true/false to ignore the given extensions or not.
  // 5. writeToFile(vector<string> ignore_dirs, vector<string> ignore_extensions): Use this to create a tree like format (iterative till the leaf nodes) for the given directory/path. Pass list of dirs you want to ignore in ignore_dirs, and list of extensions you want to ignore in ignore_extensions (e.g. ".jpg", ".png" and not "jpg", "png")
  public:
    // This struct helps us to keep track of important information of the file
    // name - absolute path (e.g: /home/BuffetCodes/Documents/FileManager.cpp)
    // rname - just the name of the file or directory (e.g: FileManager.cpp)
    // is_dir - set to true if the entity is a directory, else false
    struct file_info {
      std::string name;
      std::string rname;
      bool is_dir;
    };

    // FileManager constructor
    // Pass the path you want to operate this FileManager with.
    // You can change the path using: <FileManagerObject>.clear(string newPath)
    FileManager(std::string path) {
      this->corePath = path;
      if(!boost::filesystem::exists(path)){
        std::cout << "Enter a valid path\n";
        exit(1);
      }
    }
    // This will clear the corePath string variable.
    void clear();
    // This will change the corePath string variable to new path.
    void clear(std::string);
    // This will print the corePath (a.k.a the path) to the console
    void info();
    // This function will list files in the path given during creating the object or while changing path using clear(newPath)
    // Arguments (not keyword args)
    // ==========
    // 1. extensions (std::vector<std::string>, default value = {}): Just list the extensions you either want to ignore or you just want to list.
    // 2. ignore_extensions (bool, default value = false): If true, the extensions passed in the list of extensions will be ignored and nost listed. If false, the extensions passed will be listed only.
    // Returns
    // ==========
    // A vector of file_info struct (see the documentation of file_info to see how to access it's elements)
    std::vector<file_info> list_files(std::vector<std::string> extensions = {}, bool ignore_extensions = false);
    // This function will write a tree like structure to file named "tree.txt" in the same folder from where the binary file is called.
    // Arguments (not keyword args)
    // ==========
    // 1. ignore_dirs (std::vector<std::string>, default value = {}): The list of dirs you want to ignore in the tree. These directories will not be expanded or iterated, the name will be listed though.
    // 2. ignore_extensions (std::vector<std::string>, default value = {}): The list of extensions you want to ignore. The extensions you want to pass should have "." (dot), like {".jpg", ".png"}
    void writeToFile(std::vector<std::string> ignore_dirs = {}, std::vector<std::string> ignore_extensions = {});
  private:
    // These are the private methods, documentation will be added later. (TODO)
    // In case you are interested, navigate to src/ folder from the GitHub repo to see the definitions

    std::string corePath;
    void writeToFileIterated(std::ofstream&, int, std::vector<std::string>, std::vector<std::string>);
    bool itemInList(std::string, std::vector<std::string>);
    file_info make_file_info(std::string, std::string, bool);
};


