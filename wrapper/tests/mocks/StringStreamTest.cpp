#include "StringStream.h"
#include "gtest/gtest.h"

#include <iostream>
namespace {

  class StringStreamTest : public ::testing::Test {

    public:
      StringStreamTest() : mock_content("This is a test"){
        stream = new StringStream();
      }
      ~StringStreamTest() {
        delete stream;
      }

      // Using raw pointers here as the class is tiny and only used in this file.
      StringStream * stream;
      std::string mock_content;


  };

  TEST_F(StringStreamTest, WriteWritesLine) {
    stream->write(mock_content);
    ASSERT_STREQ(mock_content.c_str(), stream->string_stream.str().c_str());
  }

  TEST_F(StringStreamTest, ReadReadsLine) {
    stream->write(mock_content);
    ASSERT_STREQ(mock_content.c_str(), stream->read().c_str());
  }

  TEST_F(StringStreamTest, EOFSetCorrectly) {
    ASSERT_TRUE(stream->is_eof());
    stream->write(mock_content);
    ASSERT_FALSE(stream->is_eof());
  }

  TEST_F(StringStreamTest, UnEOFResetsStream) {
    ASSERT_TRUE(stream->is_eof());
    stream->write(mock_content);
    stream->read();
    ASSERT_TRUE(stream->is_eof());

    stream->un_eof();
    ASSERT_FALSE(stream->is_eof());
    ASSERT_STREQ(mock_content.c_str(), stream->read().c_str());
  }

}  // namespace
