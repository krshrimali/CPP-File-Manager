#include "FileManager.hpp"

void FileManager::clear() {
  std::cout << "Clearing the core path\n";
  corePath.clear();
}

void FileManager::clear(std::string newPath) {
  std::cout << "Clearing file manager with new path " + newPath + "\n";
  corePath = newPath;
}

void FileManager::info() {
  std::cout << "Current path is set to: " << corePath << "\n";
}

FileManager::file_info FileManager::make_file_info(std::string filename, std::string relative_filename, bool is_dir) {
  file_info f;
  f.name = filename;
  f.rname = relative_filename;
  f.is_dir = is_dir;
  return f;
}

std::vector<FileManager::file_info> FileManager::list_files_new() {
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
  bool is_dir;
  if((dir = opendir(base_name.c_str())) != NULL) {
    while((ent = readdir(dir)) != NULL) {
      std::string relative_filename = ent->d_name;
      if(relative_filename == "." || relative_filename == "..") {
        continue ;
      }
      // list_files.push_back(base_name + ent->d_name);
      std::string filename = base_name + relative_filename;
      if(opendir(filename.c_str()) == NULL) {
        is_dir = false;
      }
      else {
        is_dir = true;
      }
      list_files.push_back(make_file_info(filename, relative_filename, is_dir)) ;
    }
    closedir(dir);

  } else {
    std::cout << "Could not open directory " << base_name.c_str() << std::endl;
    exit(-1);
  }

  return list_files ;
}

std::string spaces(int s) {
  std::string out;
  for (size_t i = 0; i < s; i++) {
    out += "    ";
  }
  return out;
}

void FileManager::writeToFileIterated(FileManager f, std::ofstream& file, int depth, std::vector<std::string> ignore_dirs) {
  std::vector<file_info> out_dir = f.list_files_new();
  ++depth;
  for (auto const& iterating_entry: out_dir) {
    if (!iterating_entry.is_dir) {
      file << spaces(depth) + "|-- " + iterating_entry.rname + "\n";
    } else {
      // It's a directory
      file << spaces(depth) + "|-- " + iterating_entry.rname + "\n";
      if (dirTobeIgnored(iterating_entry.rname, ignore_dirs)) {
        std::cout << "Found true for: " << iterating_entry.rname << "\n";
        continue;
      }
      f.clear(iterating_entry.name);
      f.writeToFileIterated(f, file, depth, ignore_dirs);
    }
  }   
}

bool FileManager::dirTobeIgnored(std::string dir_name, std::vector<std::string> dirs_list) {
  if (dirs_list.size() == 0) {
    std::cout << "It says empty size" << std::endl;
    return false;
  }

  for(auto const& dir: dirs_list) {
    if (dir == dir_name) {
      return true;
    }
  }
  return false;
}

void FileManager::writeToFile(FileManager f, std::vector<std::string> ignore_dirs = {}) { 
  std::vector<file_info> out = f.list_files_new();
  std::ofstream file;
  file.open("sample_out.txt");
  if (!file.is_open()) {
    std::cout << "Unable to open the file, please check\n";
    return;
  }
  int depth = 0;
  for (auto const& entry: out) {
    if (!entry.is_dir) {
      // entry is a file
      file << "|-- " + entry.rname + "\n";
    } else {
      // entry is a directory
      file << "|-- " + entry.rname + "\n";
      std::cout << "Checking " << entry.rname << " against build" << std::endl; 
      if (dirTobeIgnored(entry.rname, ignore_dirs)) {
        std::cout << "Found true for: " << entry.rname << std::endl;
        continue;
      } else {
        f.clear(entry.name);
        f.writeToFileIterated(f, file, depth, ignore_dirs);
      }
      // f.clear(entry.name); 
      // // f.writeToFileIterated(f, file, ++depth);
      // std::vector<file_info> out_dir = f.list_files_new();
      // for (auto const& iterating_entry: out_dir) {
      //   if (!iterating_entry.is_dir) {
      //     // it's a file
      //     file << "    |-- " + iterating_entry.rname + "\n";
      //   } else {
      //     file << "    |-- " + iterating_entry.rname + "\n";
      //     std::cout << ignore_dirs.size() << std::endl;
      //     std::cout << "Checking " << iterating_entry.rname << " against build" << std::endl; 
      //     if (dirTobeIgnored(iterating_entry.rname, ignore_dirs)) {
      //       std::cout << "Found true for: " << iterating_entry.rname << std::endl;
      //     } else {
      //       f.clear(iterating_entry.name); 
      //       f.writeToFileIterated(f, file, ++depth);
      //     }
      //   }
      // }
    }
  }
  std::cout << "Done!\n";
  file.close();
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
