#pragma once

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>

#include "queue/QueueManager.h"

class Torrenter {
  public:
    Torrenter(const QueueManager & queue_manager, std::string & output_directory);
    void start();
  private:
    QueueManager & queue;
    std::string & output_dir;
    lt::session torrent_session;
    lt::torrent_handle current_handle;

    std::unique_ptr<Download> get_next();
    bool currently_downloading();

};
