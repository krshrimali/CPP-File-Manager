![CI](https://github.com/BuffetCodes/CPP-File-Manager/workflows/CI/badge.svg)

# CPP-File-Manager

The C++ File Manager provides the following functions to users:

1. `clear()` - Clears the memory allocated to corePath.
2. `clear(std::string new_path)` - Assigns a new path to the corePath variable.
3. `info()` - Prints the corePath assigned to the FileManager object to the console.
4. `list_files(std::vector<std::string> extensions, bool ignore_extensions)` - Lists the files and directories in corePath. The first argument is *extensions* which is a vector of file extensions to be ignored. These extensions are ignored only when the second argument i.e. `ignore_extensions` is set to `true`.
5. `writeToFile(std::vector<string> ignore_dirs, std::vector<std::string> ignore_extension)` - Writes the tree structure for the files and directories in corePath into a `.txt` file. This functions iterates till the innermost files of all the directories. The first argument `ignore_dirs` contains a vector of directories to be ignored in the tree structures. Similarly, the second argument `ignore_extensions` contains a vector of files extensions to be ignored in the final tree structure.

# Usage 

## Binary

The **fmanager** binary has the following options :

```
  -h  --help                        Print usage. 
  -p  --path filePath               Input path (to be iterated). 
  -l  --list_files                  Call the list files function. 
  -t  --tree                        Call the tree function. 
  -d --ignore_dirs dir1,dir2        Ignore dirs while creating tree 
  -e --ignore_extensions ext1,ext2  Ignore extensions while creating tree 
  ```

### 1. Listing files in a directory    

Command: `fmanager -p samples`

By default, it will list files in the given directory (here `samples`). Output will look like this:

```bash
Got path: samples
sample.cpp
README.md
libcpp-file-manager.a
CMakeLists.txt
FileManager.hpp
```

### 2. Building tree of the given directory and ignoring directories and extensions

`./fmanager -p ./ -t -d include,.git -e .cpp`\
_OR_ \
`./fmanager --path ./ --tree --ignore_dirs include,.git --ignore_extensions .cpp`

``` 
Got path: ./
tree.txt
CMakeLists.txt
samples
src
.github
README.md
.git
include
```

The `tree.txt` file stores the following directory structure:

```
|-- tree.txt
|-- CMakeLists.txt
|-- samples
    |-- libcpp-file-manager.a
    |-- CMakeLists.txt
    |-- README.md
    |-- FileManager.hpp
|-- src
|-- .github
    |-- workflows
        |-- build-filemanager.yml
|-- README.md
|-- .git
|-- include
```

## Using the library in your C+++ Code

`CPP-File-Manager` can be used in your C++ program as follows:

1. Create an object of `Filemanager` Class and initialize it with a path:

``` 
FileManager file(path);
```

2. The `file.list_files()` fucntion returns a vector containing names of files/directories with additional information. We can iterate through it as follows:

```cpp
for (auto const& item: file.list_files()) {
    // Use item.rname if you want "just" the name of the file or folder
    // item.name returns absolute path (with respect to the path given)
    std::cout << item.name << "\n";
}
```

The output will be as follows:

```
./tree.txt
./CMakeLists.txt
./samples
./src
./.github
./README.md
./.git
./include
```

3. The `file.writeToFile()` call, creates a text file `tree.txt` representing the directory structure: 

```cpp
std::vector<std::string> ignore_dirs = {".git", ".github", ".vscode", "build"};
std::vector<std::string> ignore_extensions = {".pyc", ".swp"};
file.writeToFile(/*ignore_folders=*/ ignore_dirs, /*ignore_extensions=*/ ignore_extensions);
```
