// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include "Logging.hpp"

void set_logs(){
  // Событие с уровнем логирования - trace
  auto TraceFileLogger = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/kseniya/lab6/logs/"
          "TraceLog_%N.log",
      boost::log::keywords::rotation_size = 10 * 1024 * 1024,
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Событие с уровнем логирования - info
  auto InfoFileLogger = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/kseniya/lab6/logs/"
          "TraceLog_%N.log",
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Событие вывода в консоль
  auto consoleLogger = boost::log::add_console_log(
      std::cout, boost::log::keywords::format =
                     "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");

  TraceFileLogger->set_filter(boost::log::trivial::severity ==
                              boost::log::trivial::trace);
  InfoFileLogger->set_filter(boost::log::trivial::severity ==
                             boost::log::trivial::info);
  consoleLogger->set_filter(boost::log::trivial::severity ==
                            boost::log::trivial::info);
}
