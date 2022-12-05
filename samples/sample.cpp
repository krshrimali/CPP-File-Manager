#include "FileManager.hpp"
#include <cstdlib>
#include <getopt.h>
#include <iostream>

const char *program_name = "fmanager"; // Use for printing usage

void print_usage() {
  printf("Usage: %s options\n", program_name);
  printf("  -h  --help                        Print usage.\n"
         "  -p  --path filePath               Input path (to be iterated).\n"
         "  -l  --list_files                  Call the list files function.\n"
         "  -t  --tree                        Call the tree function.\n"
         "  -d --ignore_dirs dir1,dir2        Ignore dirs while creating tree\n"
         "  -e --ignore_extensions ext1,ext2  Ignore extensions while creating "
         "tree\n"
         "  -s --separator                    Separator you want for your tree "
         "output\n");
  exit(-1);
}

std::vector<std::string> split(std::string s, std::string delimiter) {
  size_t pos = 0;
  std::vector<std::string> output;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    std::string token = s.substr(0, pos);
    output.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  output.push_back(s);
  return output;
}

int main(int argc, char **argv) {
  const char *short_options = "hp:s:ltd:e:";
  const struct option long_options[] = {{"help", 0, nullptr, 'h'},
                                        {"path", 1, nullptr, 'p'},
                                        {"separator", 1, nullptr, 's'},
                                        {"list_files", 0, nullptr, 'l'},
                                        {"tree", 0, nullptr, 't'},
                                        {"ignore_dirs", 1, nullptr, 'd'},
                                        {"ignore_extensions", 1, nullptr, 'e'},
                                        {nullptr, 0, nullptr, 0}};

  std::string path = "";
  std::string separator = "";
  bool list_files = true;
  bool draw_tree = false;
  int opt;
  std::vector<std::string> ignore_dirs = {};
  std::vector<std::string> ignore_extensions = {};

  do {
    opt = getopt_long(argc, argv, short_options, long_options, NULL);
    switch (opt) {
    case 'h': /* -h or --help */
      // Print usage information
      print_usage();
      break;
    case 'p': /* -p or --path */
      path = optarg;
      break;
    case 'l': /* -l or --list_files */
      list_files = true;
      break;
    case 't': /* -t or --tree */
      draw_tree = true;
      break;
    case 'd': /* -d or --ignore_dirs */
      ignore_dirs = split(optarg, ",");
      break;
    case 'e': /* -e or --ignore_extensions */
      ignore_extensions = split(optarg, ",");
      break;
    case 's':
      separator = optarg;
      break;
    case -1: /* Done with options */
      break;
    default: /* Unexpected */
      abort();
    }
  } while (opt != -1);

  if (path == "") {
    // By default use the current folder as the path
    path = ".";
  }

  FileManager *file;
  if (separator != "") {
    file = new FileManager(path, separator);
  } else {
    file = new FileManager(path);
  }
  // file.info(); // Prints the path you entered to the console
  if (list_files) {
    for (auto const &item : file->list_files()) {
      std::cout << item.rname << std::endl;
    }
  }
  if (draw_tree) {
    file->writeToFile(/*ignore_folders=*/ignore_dirs,
                      /*ignore_extensions=*/ignore_extensions);
  }
}
