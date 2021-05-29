#include "FileManager.hpp"

void FileManager::clear() {

  debugln("Clearing the core path");

  corePath.clear();
}

void FileManager::clear(std::string newPath) {

  debugln("Clearing file manager with new path", newPath);

  corePath = newPath;
}

void FileManager::info() {
  std::cout << "Current path is set to: " << corePath << "\n";
}

FileManager::file_info FileManager::make_file_info(std::string filename, std::string relative_filename, bool is_dir) {
  // f.name is the absolute name
  // f.rname is name of the folder/file
  // f.is_dir is set to true if it's a directory, else false
  file_info f;
  f.name = filename;
  f.rname = relative_filename;
  f.is_dir = is_dir;
  return f;
}

std::vector<FileManager::file_info> FileManager::list_files(std::vector<std::string> extensions, bool ignore_extensions) {
  // This returns the list of files present in the folder: corePath
  // TODO: Add tests, check if corePath is not empty
  
  std::vector<file_info> list_files;
  std::string base_name;

  if(*corePath.rbegin() != '/') base_name = corePath + "/";
  else base_name = corePath;

  debugln("Listing files and dirs in:", corePath);

  DIR* dir;
  struct dirent *ent;
  bool is_dir;
  if((dir = opendir(base_name.c_str())) != NULL) {
    while((ent = readdir(dir)) != NULL) {
      bool include = false;
      std::string relative_filename = ent->d_name;
      if(relative_filename == "." || relative_filename == "..") {
        continue;
      }
      std::string filename = base_name + relative_filename;
      if(opendir(filename.c_str()) == NULL) {

        debugln(filename, "is not a directory");

        // Check extension
        const char* const_relative_filename = relative_filename.c_str();
        auto pos = std::strrchr(const_relative_filename, '.');
        // std::string::size_type pos = relative_filename.find(".");
        // if (pos != std::string::npos) {
        if (pos) {
          // std::string file_extension = relative_filename.substr(pos);
          std::string file_extension = relative_filename.substr(pos - relative_filename.c_str());
          if (extensions.size() == 0) include = true;
          if (itemInList(file_extension, extensions) != ignore_extensions) {

            debugln("File:", filename, "with extension:",file_extension,"is being ignored.");

            // TODO: We can set include to ignore_extensions here
            include = true;
          }
        }

        is_dir = false;
      }
      else {

        debugln(filename, "is a directory");

        is_dir = true;
        include = true;
      }
      if (include) {
        list_files.push_back(make_file_info(filename, relative_filename, is_dir));
      }
    }
    closedir(dir);
  } else {
    std::cout << "Could not open directory " << base_name.c_str() << std::endl;
  }
  return list_files;
}

std::string spaces(int s) {
  std::string out;
  for (size_t i = 0; i < s; i++) {
    out += "    ";
  }
  return out;
}

void FileManager::writeToFileIterated(std::ofstream& file, int depth, std::vector<std::string> ignore_dirs, std::vector<std::string> extensions_to_ignore) {
  std::vector<file_info> out_dir = this->list_files(extensions_to_ignore, true);
  ++depth;
  for (auto const& iterating_entry: out_dir) {
    if (!iterating_entry.is_dir) {
      // it's a file
      file << spaces(depth) + "|-- " + iterating_entry.rname + "\n";
    } else {
      // It's a directory
      file << spaces(depth) + "|-- " + iterating_entry.rname + "\n";
      if (itemInList(iterating_entry.rname, ignore_dirs)) {

        debugln("Ignoring dir:", iterating_entry.name);

        continue;
      }
      this->clear(iterating_entry.name);
      this->writeToFileIterated(file, depth, ignore_dirs, extensions_to_ignore);
    }
  }   
}

bool FileManager::itemInList(std::string item, std::vector<std::string> list) {
  if (list.size() == 0) {

    debugln("Nothing passed in ignore_dirs, returning false by default then.");

    return false;
  }

  for(auto const& _item: list) {
    if (_item == item) {
      return true;
    }
  }
  return false;
}

void FileManager::writeToFile(std::vector<std::string> ignore_dirs, std::vector<std::string> ignore_extensions) { 
  std::vector<file_info> out = this->list_files(ignore_extensions, true);
  if (out.size() == 0) {

    debugln("We got no files in the folder, enable DEBUG flag to see what happened.");

    return;
  }
  std::ofstream file;
  file.open("tree.txt");
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

      debugln("Checking",entry.rname,"against build"); 

      if (itemInList(entry.rname, ignore_dirs)) {

        debugln("Ignoring dir:", entry.name);

        continue;
      } else {
        this->clear(entry.name);
        this->writeToFileIterated(file, depth, ignore_dirs, ignore_extensions);
      }
    }
  }
  debugln("Done!");
  file.close();
}


// Variadic Debug Function without new line at the end
void debug() {
    return;
}
template <typename T, typename... Types>
void debug(T var1, Types... var2) {
#ifdef DEBUG
    std::cout << var1 << " ";
    debug(var2...);
#endif
}

// Variadic Debug Function with new line at the end
void debugln() {
    std::cout<< "\n";
}
template <typename T, typename... Types>
void debugln(T var1, Types... var2) {
#ifdef DEBUG
    std::cout << var1 << " ";
    debugln(var2...);
#endif
}
