// Copyright 2021 Petrova Kseniya <ksyushki5@yandex.ru>

#include "CalcHash.hpp"

// Флаги
std::atomic<bool> continue_flag = true;
std::atomic<bool> load_json_flag = false;
//значение хеш-функции должно заканчиваться на N=4 нулей
const char correct_end_of_hash[] = "0000";
const size_t N = 4;

void stop(int flag) {
  if (flag == SIGINT) {
    continue_flag = false;
  }
}

void calculation(Load_json& j){
  //Пока не нажали  ctrl+c
  while (continue_flag) {
    std::string rand_str = std::to_string(std::rand());
    // Генерация шестнадцатеричной строки хеша SHA256 из std::string
    std::string hash = picosha2::hash256_hex_string(rand_str);
    //Время
    std::time_t timestamp(std::time(nullptr));
    //Проверка 4-х нулей в конце
    std::string hash_end = hash.substr(hash.size() - N);
    //Если нашли, логирование с уровнем info в лог и в консоль
    if (hash_end == correct_end_of_hash) {
      // Уровень логирования для данного события info - нашли нужный хеш
      BOOST_LOG_TRIVIAL(info)
          << "[ HASH - " << hash
          << "| DATA - " << rand_str << " ]";
      //Сохраняем подходящие хеши в файл json
      if (load_json_flag) {
        j.make_item(rand_str, hash, timestamp);
      }
    } else {
      //В противном случае - хеш не подходит - уровень логирования - trace
      BOOST_LOG_TRIVIAL(trace)
          << "[ HASH - " << hash
          << "| DATA - " << rand_str << " ]";
    }
  }
}

void start(const int& argc, char **argv){
  unsigned int M = 0; // потоки
  std::string path_to_json_file;
  std::srand(time(nullptr));
  switch (argc) {
      //Если не задано аргумента для количества потоков
      //Используем std::thread::hardware_concurrency();
      //В противном случае 1- й аргумент - кол-во потоков
    case 1:
      throw std::runtime_error(" No arguments!");
      break;
    case 2: {
      std::string input = argv[1];
      if (input.length() <= 10) {
        throw std::runtime_error(" No path to json-file!");
      } else {
        path_to_json_file = argv[1];
        M = std::thread::hardware_concurrency();
        load_json_flag = true;
      }
    }
    break;
    case 3: {
      M = std::atoi(argv[1]);
      if (M == 0 || M > std::thread::hardware_concurrency()) {
        throw std::runtime_error(" Incorrect count of threads!");
      }else{
        path_to_json_file = argv[2]; //второй аргумент - путь до файла
        load_json_flag = true;
      }
    }
    break;
    default:
      throw std::runtime_error(" Incorrect count of arguments!!!");
  }
  //Запускаем логирование
  set_logs();
  boost::log::add_common_attributes();
  //Создаём и синхронизируем потоки
  std::vector<std::thread> threads;
  threads.reserve(M);

  //Здесь будут храниться нужные результаты
  //Для вывода в файл
  Load_json json_obj;

  //Обрабатываем ctrl+c
  std::signal(SIGINT, stop);

  for (size_t i = 0; i < M; i++) {
    //Запускаем расчёт хешей в M потоках
    threads.emplace_back(calculation, std::ref(json_obj));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  //Сохраняем результат
  if (load_json_flag) {
    std::ofstream fout{path_to_json_file};
    fout << json_obj;
  }
}
