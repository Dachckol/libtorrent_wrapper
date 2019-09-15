#include "torrent/Torrenter.h"

Torrenter::Torrenter(const QueueManager & queue_manager, std::string & output_directory):
  queue(queue_manager),
  torrent_session(),
  output_dir(output_directory),
{
}

void Torrenter::start(){
  std::cout << "Starting libtorrent..." << std::endl;

  for (;;) {
    if (!currently_downloading) {
      get_next();
    }
  }
}

bool currently_downloading() {
  return true;
}

std::unique_ptr<Download> Torrenter::get_next() {
  return queue.pop();
}
