#include "queue/QueueManager.h"

QueueManager::QueueManager(Stream & queue_stream): stream(queue_stream) {}

void QueueManager::add(Download & download) {
}

void QueueManager::remove(std::string & name) {
}

std::shared_ptr<Download> QueueManager::pop() {
  auto list = read();
}

std::vector<std::shared_ptr<Download>> QueueManager::read() {
  
}
