#include "FileManager.hpp"
void FileManager::clear(){
  #ifdef DEBUG
    std::cout << "Clearing the core Path\n";
  #endif
  corePath.clear();
}

void FileManager::clear(std::string newPath){
  #ifdef DEBUG
    std::cout << "Clearing file manager with new path " + newPath + "\n";
  #endif
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

std::vector<FileManager::file_info> FileManager::list_files(std::vector<std::string> extensions, bool ignore_extensions){
  std::vector<boost::filesystem::directory_entry> store; // To save the file names in a vector.
  std::vector<FileManager::file_info> list_files;
  std::string base_name;
  if(*corePath.rbegin() != '/') base_name = corePath+"/";
  else base_name = corePath;

  #ifdef DEBUG
    std::cout << "Listing files and directories in : " << corePath << "\n";
  #endif

  boost::filesystem::path inputPath(base_name);

  if(boost::filesystem::is_directory(inputPath)){
        copy(boost::filesystem::directory_iterator(inputPath), boost::filesystem::directory_iterator(), back_inserter(store));

        for ( std::vector<boost::filesystem::directory_entry>::const_iterator it = store.begin(); it != store.end();  ++ it ){
            std::string filename = (*it).path().string();
            // Boost filesystem always gives full filename
            // Extracting relative filename
            std::string relative_filename = filename.substr(base_name.size(),filename.size()-base_name.size()+1);
            bool is_dir,include;
            if(!boost::filesystem::is_directory(boost::filesystem::path(filename))){
              #ifdef DEBUG
                std::cout << filename << " is not a directory" << std::endl;
              #endif
              // Getting file extension
              std::string file_extension = boost::filesystem::extension(filename);
              if(itemInList(file_extension,extensions) && ignore_extensions){
                #ifdef DEBUG
                  std::cout << "File: " << filename << " with extension: " << file_extension << " is being ignored.\n";
                #endif
                include = false;
              }else{
                include = true;
              }
              is_dir = false;
            }else{
              #ifdef DEBUG
                std::cout << filename << " is a directory" << std::endl;
              #endif
              is_dir = true;
              include = true;
            }
            if(include){
              list_files.push_back(make_file_info(filename,relative_filename,is_dir));
            }
        }    
  }else{
    std::cout << "Could not open directory !!\n";
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


void FileManager::writeToFileIterated(std::ofstream &file, int depth, std::vector<std::string> ignore_dirs,std::vector<std::string> extensions_to_ignore){
  std::vector<file_info> out_dir = this->list_files(extensions_to_ignore,true);
  ++depth;
  for(auto const &iterating_entry : out_dir){
    if(!iterating_entry.is_dir){
      // it's a file
      file << spaces(depth) << "|-- " + iterating_entry.rname + "\n";
    }else{
      // it's a directory
      file << spaces(depth) << "|-- " + iterating_entry.rname + "\n";
      if(itemInList(iterating_entry.rname,ignore_dirs)){
        #ifdef DEBUG
            std::cout << "Ignoring dir: " << iterating_entry.name << "\n";
        #endif
        continue;
      }
      this->clear(iterating_entry.name);
      this->writeToFileIterated(file,depth,ignore_dirs,extensions_to_ignore);
    }
  }
}


void FileManager::writeToFile(std::vector<std::string> ignore_dirs,std::vector<std::string> ignore_extensions){
  std::vector<file_info> out = this->list_files(ignore_extensions,true);
  if(out.size() == 0){
    #ifdef DEBUG
      std::cout << "We got no files in the folder, enable DEBUG flag to see what happened.\n";
    #endif
    return;
  }
  std::ofstream file;
  file.open("tree.txt");

  if(!file.is_open()){
    std::cout << "Unable to open the file, please check \n";
    return;
  }

  int depth = 0;
  for(auto const &entry : out){
    if(!entry.is_dir){
      // entry is a file
      file << "|-- " + entry.rname + "\n";
    }else{
      // entry is a directory
      file << "|-- " + entry.rname + "\n";
      #ifdef DEBUG
        std::cout << "Checking " << entry.rname << " against the build\n";
      #endif
      if(itemInList(entry.rname,ignore_dirs)){
        #ifdef DEBUG
          std::cout << "Ignoring dir : " << entry.name << "\n";
        #endif
        continue;
      }else{
        this->clear(entry.name);
        this->writeToFileIterated(file,depth,ignore_dirs,ignore_extensions);
      }
    }
  }
  #ifdef DEBUG
      std::cout << "Done !\n";
  #endif
  file.close();
}

bool FileManager::itemInList(std::string item, std::vector<std::string> list) {
  if (list.size() == 0) {
    #ifdef DEBUG
      std::cout << "Nothing passed in ignore_dirs, returning false by default then." << std::endl;
    #endif
    return false;
  }

  for(auto const& _item: list) {
    if (_item == item) {
      return true;
    }
  }
  return false;
}