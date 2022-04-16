// Copyright 2022 Petrova Kseniya <ksyushki5@yandex.ru>

#include "Logging.hpp"

void set_logs(){
  //уровень логирования - trace
  auto trace_log = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/kseniya/lab6/logs/"
          "TraceLog_%N.log",
      boost::log::keywords::rotation_size = 10 * 1024 * 1024,
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  //уровень логирования - info
  auto info_log = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/home/kseniya/lab6/logs/"
          "TraceLog_%N.log",
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  //вывод в консоль
  auto console_log = boost::log::add_console_log(
      std::cout, boost::log::keywords::format =
                     "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  //выставляем фильтры на логи
  trace_log->set_filter(boost::log::trivial::severity ==
                              boost::log::trivial::trace);
  info_log->set_filter(boost::log::trivial::severity ==
                             boost::log::trivial::info);
  console_log->set_filter(boost::log::trivial::severity ==
                            boost::log::trivial::info);
}
