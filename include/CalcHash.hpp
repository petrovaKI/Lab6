// Copyright 2022 Petrova Kseniya <ksyushki5@yandex.ru>

#ifndef INCLUDE_CALCHASH_HPP_
#define INCLUDE_CALCHASH_HPP_


#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <csignal>
#include <nlohmann/json.hpp>
#include <picosha2.h>
#include "Logging.hpp"
#include "MakeJson.hpp"

using nlohmann::json;

//Ctri+C
void stop(int flag);

void calculation(Load_json& j);
void start(const int& argc, char **argv);

#endif  // INCLUDE_CALCHASH_HPP_
