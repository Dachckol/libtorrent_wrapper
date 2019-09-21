#pragma once

#include <string>
#include <fstream>

#include "queue/stream/Stream.h"

class FileOpenException: public std::exception{
  virtual const char* what() const throw() {
    return "Failed to open file";
  }
};

class FileCloseException: public std::exception{
  virtual const char* what() const throw() {
    return "Failed to close file";
  }
};

class FileStream : public Stream {
  public:
    FileStream(const std::string & file_name);
    void write(const std::string content) override;
    std::string read() override;
    bool is_eof() override;
    void clear() override;
    void un_eof() override;
    void reload() override;
    ~FileStream();
  private:
    std::fstream file_stream;
    const std::string & file;
    void open();
    void open_clear();
    bool has_read;
};
