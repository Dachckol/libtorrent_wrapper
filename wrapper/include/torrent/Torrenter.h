#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/magnet_uri.hpp>

#include "queue/QueueManager.h"

typedef lt::alert const* TorrentAlertPtr;
class Torrenter {
  public:
    Torrenter(QueueManager & queue_manager, std::string & output_directory);
    void start_downloading();
  private:
    QueueManager & queue;
    std::string & output_dir;
    lt::session torrent_session;
    lt::torrent_handle current_handle;
    lt::settings_pack session_settings;

    void configure_session();
    void start_next_torrent();
    lt::add_torrent_params get_next();
    bool handle_status_events_ok();
    std::vector<lt::alert*> get_alerts();

    static void log_alert(TorrentAlertPtr a);
    static bool is_finished_alert(TorrentAlertPtr a);
    static bool is_failed_alert(TorrentAlertPtr a);
    static void pause_thread(int seconds);
};
