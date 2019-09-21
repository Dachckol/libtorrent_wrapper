#include "queue/QueueManager.h"

QueueManager::QueueManager(Stream & queue_stream): stream(queue_stream) {}

void QueueManager::add(const Download & download) {
  std::stringstream download_entry;
  download_entry << download.name;
  download_entry << " ";
  download_entry << download.magnet_url;
  download_entry << std::endl;

  stream.write(download_entry.str());
}

void QueueManager::remove(const std::string & name) {
  std::stringstream filtered_entries;

  bool first = true;
  while(!stream.is_eof()) {
    std::string line = stream.read();
    if (line.find(name) == std::string::npos)
    {
      if (first){
        first = false;
      } else filtered_entries << std::endl;
      filtered_entries << line;
    }
  }

  try {
    stream.clear();
  } catch (std::exception e) {
    throw e;
  }

  stream.write(filtered_entries.str());
  stream.un_eof();
}

Download QueueManager::pop() {
  if (is_eof()){
    throw StreamAtEOF();
  }
  auto download = to_download(stream.read());

  remove(download.name);

  return download;
}

Download QueueManager::to_download(const std::string entry) {
  Download download;

  std::stringstream entry_stream(entry);
  getline(entry_stream, download.name, ' ');
  getline(entry_stream, download.magnet_url);

  return download;
}

bool QueueManager::is_eof() {
  stream.reload();
  return stream.is_eof();
}
