#include "StringStream.h"
#include "Download.h"
#include "queue/QueueManager.h"
#include "gtest/gtest.h"

#include <iostream>
namespace {

  class QueueManagerTest : public ::testing::Test {

    public:
      QueueManagerTest() {
        stream = new StringStream();
        queue = new QueueManager(*stream);

        mock_download.name = "Test";
        mock_download.magnet_url = "http://google.com";

        mock_download1.name = "Test1";
        mock_download1.magnet_url = "http://google.com";
      }
      ~QueueManagerTest() {
        delete queue;
        delete stream;
      }

      std::string download_to_string(const Download & download) {
        std::stringstream stream;
        stream << download.name;
        stream << " ";
        stream << download.magnet_url;
        return stream.str();
      }


      // Using raw pointers here as the class is tiny and only used in this file.
      StringStream * stream;
      QueueManager * queue;
      Download mock_download;
      Download mock_download1;
  };

  TEST_F(QueueManagerTest, AddAddsDownloadToStream) {
    queue->add(mock_download);
    ASSERT_STREQ(
        download_to_string(mock_download).c_str(),
        stream->read().c_str()
        );
  }


  TEST_F(QueueManagerTest, RemoveRemovesEntryFromStream) {
    queue->add(mock_download);
    queue->add(mock_download1);
    queue->remove(mock_download1.name);

    while(!stream->is_eof()) {
      std::string line = stream->read();
      ASSERT_FALSE(line.find(mock_download1.name));
    }
  }

  TEST_F(QueueManagerTest, PopReturnsAndRemoves) {
    queue->add(mock_download1);
    queue->add(mock_download);

    auto download = queue->pop();

    ASSERT_STREQ(mock_download1.name.c_str(), download.get()->name.c_str());
    ASSERT_STREQ(mock_download1.magnet_url.c_str(), download.get()->magnet_url.c_str());

    while(!stream->is_eof()) {
      std::string line = stream->read();
      ASSERT_FALSE(line.find(mock_download1.name));
    }
  }
}  // namespace
