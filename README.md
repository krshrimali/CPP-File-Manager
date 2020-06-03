![CI](https://github.com/HimanshuSinghGH/CPP-File-Manager/workflows/CI/badge.svg)

# CPP-File-Manager

CPP-File-Manager is an easy to use Open-Source C++ library for listing files and directories at a particular location. 

It consists of the following functions :

__1. Clear()__ - Clears the memory allocated to corePath.__

__2. Clear(string *new_path*)__ - Assigns a new path to the corePath variable.

__3. Info( )__ - Prints the corePath assigned to the FileManager object to the console.__

__4. list_files(vector<string> extensions, bool ignore_extensions)__ - Lists the files and directories in corePath. The first argument is *extensions* which is a vector of file extensions to be ignored. These extensions are ignored only when the second argument i.e. *ignore_extensions* is set to **True**.

__5. writeToFile(vector<string> ignore_dirs, vector<string> ignore_extension)__ - Writes the tree structure for the files and directories in corePath into a __.txt__ file. This functions iterates till the innermost files of all the directories. The first argument *ignore_dirs* contains a vector of directories to be ignored in the tree structures. Similarly, the second argument *ignore_extensions* contains a vector of files extensions to be ignored in the final tree structure.