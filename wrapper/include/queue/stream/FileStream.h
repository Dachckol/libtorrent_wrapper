#pragma once

#include <string>
#include <fstream>

#include "queue/stream/Stream.h"

class FileStream : public Stream {
  public:
    FileStream(const std::string & file_name);
    void write(const std::string & content);
    std::string read();
    ~FileStream();
  private:
    std::fstream file_stream;
};
