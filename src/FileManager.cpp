#include "FileManager.hpp"

void FileManager::clear() {
  std::cout << "Clearing the core path\n";
  corePath.clear();
}

void FileManager::clear(std::string newPath) {
  std::cout << "Clearing file manager with new path\n";
  corePath = newPath;
}

void FileManager::info() {
  std::cout << "Current path is set to: " << corePath << "\n";
}

file_info FileManager::make_file_info(std::string filename, bool is_dir) {
  file_info f ;
  f.name = filename ;
  f.is_dir = is_dir ;
  return f ;
}

std::vector<std::string> FileManager::list_files() {
  // This returns the list of files present in the folder: corePath
  // TODO: Add tests, check if corePath is not empty
  // Converting #ifdef NDEBUG and #endif to a macro

  #ifdef NDEBUG
    assert(corePath != "");
  #endif

  std::vector<std::string> list_files;
  std::string base_name;

  if(*corePath.rbegin() != '/') base_name = corePath + "/";
  else base_name = corePath;

  DIR* dir;
  struct dirent *ent;
  if((dir = opendir(base_name.c_str())) != NULL) {
    while((ent = readdir(dir)) != NULL) {
  #ifdef NDEBUG
      std::cout << "Reading filename from directory: " << base_name << std::endl;
  #endif
      std::string filename = ent->d_name;
  #ifdef NDEBUG
      std::cout << "Filename: " << filename << "\n";
  #endif
      list_files.push_back(base_name + ent->d_name);
    }
  #ifdef NDEBUG
    std::cout << "Closing dir" << std::endl;
  #endif
    closedir(dir);
  #ifdef NDEBUG
    std::cout << "Closed dir" << std::endl;
  #endif
  } else {
      std::cout << "Could not open directory " << base_name.c_str() << std::endl;
      exit(-1);
  }

  return list_files;
}


std::vector<file_info> FileManager::list_files_new() {
  // This returns the list of files present in the folder: corePath
  // TODO: Add tests, check if corePath is not empty
  // Converting #ifdef NDEBUG and #endif to a macro
  //std::vector<std::string> list_files;
  std::vector<file_info> list_files ;
  std::string base_name;

  if(*corePath.rbegin() != '/') base_name = corePath + "/";
  else base_name = corePath;

  DIR* dir;
  struct dirent *ent;
  bool is_dir ;
  if((dir = opendir(base_name.c_str())) != NULL) {

    while((ent = readdir(dir)) != NULL) {
      std::string filename = ent->d_name;
      if(filename == "." || filename == "..") {
        continue ;
      }
      // list_files.push_back(base_name + ent->d_name);
      filename = base_name + filename ;
      if(opendir(filename.c_str()) == NULL) {
        is_dir=false;
      }
      else {
        is_dir=true;
      }

      list_files.push_back(make_file_info(filename,is_dir)) ;
    }
    closedir(dir);

  } else {
      std::cout << "Could not open directory " << base_name.c_str() << std::endl;
      exit(-1);
  }

  return list_files ;
}