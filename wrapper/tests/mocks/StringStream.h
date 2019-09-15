#pragma once

#include <string>
#include <sstream>

#include "queue/stream/Stream.h"

class StringStream : public Stream {
  public:
    std::stringstream string_stream;

    StringStream() : string_stream() {};

    void write(const std::string & content) {
      this->string_stream << content;
    };

    std::string read() {
      std::string content;
      getline(this->string_stream, content);
      return content;
    };

};
