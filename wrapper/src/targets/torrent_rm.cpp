#include <iostream>
#include "queue/QueueManager.h"
#include "queue/stream/FileStream.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "ERROR: Invalid number of options provided" << std::endl;
    std::cerr << "arguments: [file] [name]" << std::endl;
    return 0;
  }

  std::string file_name = argv[1];
  std::string name = argv[2];

  try {
    FileStream stream(file_name);
    QueueManager(stream).remove(name);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
