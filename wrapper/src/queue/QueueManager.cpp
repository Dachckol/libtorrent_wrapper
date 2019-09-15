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

  while(!stream.is_eof()) {
    std::string line = stream.read();
    if (!line.find(name)) filtered_entries << line << std::endl;
  }

  try {
    stream.clear();
  } catch (std::exception e) {
    throw e;
  }

  stream.write(filtered_entries.str());
}

std::unique_ptr<Download> QueueManager::pop() {
  std::string top_entry = stream.read();

  auto download = to_download(top_entry);

  remove(download.get()->name);

  return download;
}

std::unique_ptr<Download> QueueManager::to_download(std::string & entry) {
  auto download = std::make_unique<Download>();

  std::stringstream entry_stream(entry);
  getline(entry_stream, download.get()->name, ' ');
  getline(entry_stream, download.get()->magnet_url);

  return download;
}
