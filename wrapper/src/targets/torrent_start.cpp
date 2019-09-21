#include <iostream>
#include <string>
#include "queue/QueueManager.h"
#include "queue/stream/FileStream.h"
#include "torrent/Torrenter.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "ERROR: Invalid number of options provided" << std::endl;
    std::cerr << "arguments: [file] [output directory]" << std::endl;
    return 0;
  }

  std::string magnet_file = argv[1];
  std::string output_dir = argv[2];

  std::cout << "Starting torrent client..." << std::endl;
  std::cout << "    * Reading files from : "<< magnet_file << std::endl;
  std::cout << "    * Output to          : "<< output_dir << std::endl;


  try {
    FileStream stream(magnet_file);
    QueueManager queue_manager(stream);
    Torrenter(queue_manager, output_dir).start_downloading();
  } catch (std::exception e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
