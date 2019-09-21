#pragma once

#include <string>
#include <sstream>

#include "queue/stream/Stream.h"

class StringStream : public Stream {
  public:
    std::stringstream string_stream;

    StringStream() : string_stream(), empty(true) {};

    void write(const std::string & content) override {
      empty=false;
      this->string_stream << content;
    };

    std::string read() override {
      std::string content;
      getline(this->string_stream, content);
      return content;
    };

    bool is_eof() override {
      return string_stream.eof() || empty;
    }

    void clear() override {
      string_stream.str(std::string());
    }

    void un_eof() override {
      string_stream.clear();
      string_stream.seekg(0, std::ios::beg);
    }

    void reload() override {
      un_eof();
    }

  private:
    bool empty;
};
