// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include "MakeJson.hpp"

void Load_json::make_item(const std::string& str,
                          const std::string& hash,
                          std::time_t timestamp) {
  // Зацита потока от множественного использования
  std::scoped_lock<std::mutex> lock(mut);
  // Переводим значение хеша в 16-ичную систему
  std::stringstream hex_hash;
  hex_hash << std::hex << std::uppercase << std::stoi(str);
  //uppercase - переводит в верхний регистр,
  // stoi - переводит строку в число,
  // hex - переводит число в hex
  json obj;
  obj["timestamp"] = timestamp;
  obj["hash"] = hash;
  obj["data"] = hex_hash.str();
  arr.push_back(obj);
}
std::ostream& operator<<(std::ostream& out, const Load_json& j) {
  std::scoped_lock<std::mutex> lock(j.mut);
  out << j.arr.dump(4); //dump(4) - выполняет сериализацию на 4 строки
  return out;
}
