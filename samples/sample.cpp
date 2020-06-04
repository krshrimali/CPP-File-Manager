#include <iostream>
#include "FileManager.hpp"
#include <getopt.h>
#include <cstdlib>

const char* program_name = "fmanager"; // Use for printing usage

void print_usage() {
  printf("Usage: %s options\n", program_name);
  printf("  -h  --help                   Print usage.\n",
         "  -p  --path filePath          Input path (to be iterated).\n",
         "  -l  --list_files             Call the list files function.\n",
         "  -t  --tree                   Call the tree function.\n");
  exit(-1);
}

int main(int argc, char** argv) {
  const char* short_options = "hp:lt";
  const struct option long_options[] = {
    { "help",       0,    NULL,   'h'},
    { "path",       1,    NULL,   'p'},
    { "list_files", 0,    NULL,   'l'},
    { "tree",       0,    NULL,   't'},
    { NULL,         0,    NULL,    0 }
  };

  std::string path = "";
  bool list_files = true;
  bool draw_tree = false;
  int opt;

  do {
    opt = getopt_long (argc, argv, short_options, long_options, NULL);
    switch (opt) {
      case 'h': /* -h or --help */
        // Print usage information
        print_usage();
      case 'p': /* -p or --path */
	std::cout << "Got path: " << optarg << std::endl;
	path = optarg;
        break;
      case 'l': /* -l or --list_files */
        list_files = true;
      case 't': /* -t or --tree */
        draw_tree = true;
      case -1: /* Done with options */
        break;
      default: /* Unexpected */
        abort ();
    }
  } while(opt != -1); 

  if (path == "") {
    // By default use the current folder as the path
    path = ".";
  }
  
  FileManager file(path);
  // file.info(); // Prints the path you entered to the console
  if (list_files) {
    for (auto const& item: file.list_files()) {
      std::cout << item.name << std::endl;
    }
  }
  if (draw_tree) {
    file.writeToFile(/*ignore_folders=*/ {}, /*ignore_extensions=*/ {});
  }
}
