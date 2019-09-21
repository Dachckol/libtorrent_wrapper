#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "Download.h"
#include "queue/stream/Stream.h"

class QueueManager {
  public:
    QueueManager(Stream & queue_stream);

    void add(const Download & download);
    void remove(const std::string & name);
    std::unique_ptr<Download> pop();
    bool is_eof();

  private:
    Stream & stream;

    std::unique_ptr<Download> to_download(std::string & entry);
};
