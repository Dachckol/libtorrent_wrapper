#include "queue/stream/FileStream.h"


FileStream::FileStream(const std::string & file_name) :
  file_stream(file_name) {
}

FileStream::~FileStream() {
  this->file_stream.close();
}

void FileStream::write(const std::string & content) {
  this->file_stream << content;
}

std::string FileStream::read() {
  std::string content;
  getline(this->file_stream,content);
  return content;
}
