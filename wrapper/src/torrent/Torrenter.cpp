#include "torrent/Torrenter.h"

Torrenter::Torrenter(QueueManager& queue_manager,
                     const std::string& output_directory)
    : queue(queue_manager), output_dir(output_directory), torrent_session() {
  configure_session();
}

void Torrenter::configure_session() {
  std::cout << "Configuring session settings" << std::endl;
  lt::settings_pack settings;
  settings.set_int(lt::settings_pack::alert_mask,
                   lt::alert::error_notification |
                       lt::alert::status_notification |
                       lt::alert::file_progress_notification);

  torrent_session.apply_settings(settings);
  std::cout << "Settings applied" << std::endl;
}

void Torrenter::start_downloading() {
  std::cout << "Starting downloading" << std::endl;
  start_next_torrent();
  while (handle_status_events_ok())
    ;
}

void Torrenter::start_next_torrent() {
  current_handle = torrent_session.add_torrent(std::move(get_next()));
}

lt::add_torrent_params Torrenter::get_next() {
  std::cout << "Reading queue for next torrent: " << std::endl;
  while (queue.is_eof()) {
    std::cout << "Queue is empty - waiting 1m" << std::endl;
    pause_thread(60);
  }

  std::string magnet_url, output_path;
  {
    Download download = queue.pop();
    magnet_url = std::move(download.magnet_url);
    output_path = output_dir + std::move(download.name);
  }

  std::cout << "  - " << magnet_url << std::endl;
  std::cout << "  - " << output_path << std::endl;

  auto params =
      lt::add_torrent_params(lt::parse_magnet_uri(std::move(magnet_url)));
  params.save_path = std::move(output_path);

  return params;
}

void Torrenter::pause_thread(int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

bool Torrenter::handle_status_events_ok() {
  for (TorrentAlertPtr alert : get_alerts()) {
    log_alert(alert);
    if (is_finished_alert(alert)) {
      torrent_session.remove_torrent(current_handle);
      start_next_torrent();
      break;
    } else if (is_failed_alert(alert)) {
      return false;
    }
    pause_thread(2);
  }

  return true;
}

std::vector<lt::alert*> Torrenter::get_alerts() {
  std::vector<lt::alert*> alerts;
  torrent_session.pop_alerts(&alerts);
  return alerts;
}

void Torrenter::log_alert(TorrentAlertPtr a) {
  std::cout << a->message() << std::endl;
}

bool Torrenter::is_finished_alert(TorrentAlertPtr a) {
  return lt::alert_cast<lt::torrent_finished_alert>(a);
}

bool Torrenter::is_failed_alert(TorrentAlertPtr a) {
  return lt::alert_cast<lt::torrent_error_alert>(a);
}
