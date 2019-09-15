#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Download.h"
#include "queue/stream/Stream.h"

class QueueManager {
  public:
    QueueManager(Stream & queue_stream);

    void add(Download & download);
    void remove(std::string & name);
    std::shared_ptr<Download> pop();

  private:
    std::vector<std::shared_ptr<Download>> read();
    Stream & stream;
};
