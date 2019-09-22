#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "Download.h"
#include "queue/stream/Stream.h"

class QueueManager {
 public:
  explicit QueueManager(Stream& queue_stream);

  void add(const Download& download);
  void remove(const std::string& name);
  Download pop();
  bool is_eof();

 private:
  Stream& stream;

  static Download to_download(const std::string& entry);
};
