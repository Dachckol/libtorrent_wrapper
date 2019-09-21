#pragma once

#include <iostream>

class StreamAtEOF: public std::exception{
  virtual const char* what() const throw() {
    return "Stream is empty";
  }
};

class Stream {
  public:
    virtual void write(const std::string content) = 0;
    virtual std::string read() = 0;
    virtual void reload() = 0;
    virtual bool is_eof() = 0;
    virtual void clear() = 0;
    virtual void un_eof() = 0;
};
