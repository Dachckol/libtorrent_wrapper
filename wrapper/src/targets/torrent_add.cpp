#include <iostream>
#include "queue/QueueManager.h"
#include "queue/stream/FileStream.h"
#include "Download.h"

int main(int argc, char ** argv) {
  if (argc != 4) {
    std::cerr << "ERROR: Invalid number of options provided" << std::endl;
    std::cerr << "arguments: [file] [name] [url]" << std::endl;
    return 0;
  }

  std::string file_name = argv[1];
  Download download;
  download.name = argv[2];
  download.magnet_url = argv[3];


  try {
    FileStream stream(file_name);
    QueueManager(stream).add(download);
  } catch (std::exception e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
