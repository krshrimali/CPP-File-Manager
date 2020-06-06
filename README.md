![CI](https://github.com/HimanshuSinghGH/CPP-File-Manager/workflows/CI/badge.svg)

# CPP-File-Manager

CPP-File-Manager is an easy to use Open-Source C++ library for listing files and directories at a particular location. 

It consists of the following functions :

__1. Clear()__ - Clears the memory allocated to corePath.__

__2. Clear(string *new_path*)__ - Assigns a new path to the corePath variable.

__3. Info( )__ - Prints the corePath assigned to the FileManager object to the console.__

__4. list_files(vector<string> extensions, bool ignore_extensions)__ - Lists the files and directories in corePath. The first argument is *extensions* which is a vector of file extensions to be ignored. These extensions are ignored only when the second argument i.e. *ignore_extensions* is set to **True**.

__5. writeToFile(vector<string> ignore_dirs, vector<string> ignore_extension)__ - Writes the tree structure for the files and directories in corePath into a __.txt__ file. This functions iterates till the innermost files of all the directories. The first argument *ignore_dirs* contains a vector of directories to be ignored in the tree structures. Similarly, the second argument *ignore_extensions* contains a vector of files extensions to be ignored in the final tree structure.

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

### 1. Listing files in a directory:    
` fmanager -p ./samples `

``` 
Got path: ./samples/ 
./samples/libcpp-file-manager.a 
./samples/CMakeLists.txt
./samples/sample.cpp
./samples/README.md
./samples/FileManager.hpp
```
### 2. Building tree of directory structure and ignoring directories and extensions:    
` ./fmanager -p ./ -t -d include,.git -e .cpp`\
_OR_ \
`./fmanager --path ./ --tree --ignore_dirs include,.git --ignore_extensions .cpp`

``` 
Got path: ./
./tree.txt
./CMakeLists.txt
./samples
./src
./.github
./README.md
./.git
./include
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

## CPP code

### CPP-File-Manager can be used inside a C++ program as follows:

1. Create an object of `Filemanager` Class and initialize it with a path:

``` 
FileManager file(path);
```

2. The `file.list_files()` fucntion returns a vector containing names of files/directories with additional information. We can iterate through it as follows:

``` 
for (auto const& item: file.list_files()) {
      std::cout << item.name << std::endl;
    }
```
The output generated is as follows:

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

3. The `file.writeToFile()` creates a text file `tree.txt` representing the directory structure: 

```
file.writeToFile(/*ignore_folders=*/ ignore_dirs, /*ignore_extensions=*/ ignore_extensions);
```