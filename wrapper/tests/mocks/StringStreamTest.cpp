#include "StringStream.h"
#include "gtest/gtest.h"

#include <iostream>
namespace {

  class StringStreamTest : public ::testing::Test {

    public:
      StringStreamTest() {
      }
      ~StringStreamTest() {
      }


  };

  TEST_F(StringStreamTest, WriteWritesLine) {
    StringStream stream;
    std::string content = "This is a test";

    stream.write(content);

    ASSERT_STREQ(content.c_str() ,stream.string_stream.str().c_str());
  }

  TEST_F(StringStreamTest, ReadReadsLine) {
    StringStream stream;
    std::string content = "This is a test";

    stream.write(content);

    ASSERT_STREQ(content.c_str(), stream.read().c_str());
  }

}  // namespace
