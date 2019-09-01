#include <iostream>
#include <string>

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "ERROR: Invalid number of options provided" << std::endl;
    return 0;
  }

  std::string magnet_file = argv[1];
  std::string output_dir = argv[2];

  std::cout << "Starting torrent client..." << std::endl;
  std::cout << "    * Reading files from : "<< magnet_file << std::endl;
  std::cout << "    * Output to          : "<< output_dir << std::endl;
  return 0;
}
