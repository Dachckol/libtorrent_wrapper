#pragma once

#include <iostream>

class Stream {
  public:
    virtual void write(const std::string & content) = 0;
    virtual std::string read() = 0;
    virtual bool is_eof() = 0;
    virtual void clear() = 0;
};
