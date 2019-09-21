#include "torrent/Torrenter.h"

Torrenter::Torrenter(
    QueueManager & queue_manager,
    std::string & output_directory
  ):
  queue(queue_manager),
  output_dir(output_directory),
  torrent_session()
{
  configure_session();
}


void Torrenter::configure_session() {
  std::cout << "Configuring session settings" << std::endl;
  lt::settings_pack settings;
  settings.set_int(lt::settings_pack::alert_mask,
      lt::alert::error_notification |
      lt::alert::status_notification |
      lt::alert::file_progress_notification |
      lt::alert::performance_warning
  );

  torrent_session.apply_settings(settings);
  std::cout << "Settings applied" << std::endl;
}


void Torrenter::start_downloading() {
  std::cout << "Starting downloading" << std::endl;
  start_next_torrent();
  while (handle_status_events_ok());
}

void Torrenter::start_next_torrent(){
  current_handle = torrent_session.add_torrent(std::move(get_next()));
}

lt::add_torrent_params Torrenter::get_next() {
  std::cout << "Reading queue for next torrent: " << std::endl;
  std::unique_ptr<Download> download = queue.pop();
  std::cout << "  - "<< download.get()->magnet_url << std::endl;
  auto params = lt::add_torrent_params(
      lt::parse_magnet_uri(download.get()->magnet_url)
      );

  std::string output = output_dir.append(download.get()->name);
  std::cout << "  - "<< output << std::endl;
  params.save_path = output;

  return params;
}

bool Torrenter::handle_status_events_ok() {
  for (TorrentAlertPtr alert : get_alerts() ){
    log_alert(alert);
    if ( is_finished_alert(alert) ){
      start_next_torrent();
      break;
    } else if ( is_failed_alert(alert) ){
      return false;
    }
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

