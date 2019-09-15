#include "queue/stream/FileStream.h"


FileStream::FileStream(
    const std::string & file_name) : file(file_name){
  open();
}

void FileStream::open() {
  file_stream.open(
      file,
      std::fstream::in | std::fstream::out
      );
  if (!file_stream.is_open()) throw FileOpenException();
}

FileStream::~FileStream() {
  if (file_stream.is_open())
    file_stream.close();
}

void FileStream::write(
    const std::string & content) {
  file_stream << content;
}

bool FileStream::is_eof() {
  return file_stream.eof();
}

void FileStream::clear() {
  //risky business, need to reopen the stream with trunc
  try {
    file_stream.close();
  } catch(std::ios_base::failure e) {
    if (file_stream.is_open()) {
      std::cerr << "Failed to close filestream";
      throw FileCloseException();
    }
  }
  open_clear();
}

void FileStream::open_clear() {
  file_stream.open(
      file,
      std::fstream::in | std::fstream::out | std::fstream::trunc
      );
  if (!file_stream.is_open()) throw FileCloseException();
}

std::string FileStream::read() {
  std::string content;
  getline(file_stream,content);
  return content;
}
