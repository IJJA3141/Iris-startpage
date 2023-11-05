#include "loader.hpp"

std::string HOME_DIR;

bool Iris::file_exist(std::string _file) {
  struct stat buffer;
  return (stat(_file.c_str(), &buffer) == 0);
}

Json::Value *Iris::load_condifg() {
  Json::Value *res = new Json::Value();

  if (Iris::file_exist(HOME_DIR + "/.config/iris/config.json")) {
    std::fstream stream;
    stream.open(HOME_DIR + "/.config/iris/config.json", std::ios::in);
    if (stream.is_open()) {
      stream >> *res;
      stream.close();
    } else {
      std::cerr << ERR_LOAD_CONFIG << std::endl;
      exit(ERRNUM_LOAD_CONFIG);
    }
  } else if (Iris::file_exist("/etc/iris/config.json")) {
    std::fstream stream;
    stream.open("/etc/iris/config.json", std::ios::in);
    if (stream.is_open()) {
      stream >> *res;
      stream.close();
    } else {
      std::cerr << ERR_LOAD_CONFIG << std::endl;
      exit(ERRNUM_LOAD_CONFIG);
    }
  } else {
    std::cerr << ERR_NO_CONFIG << std::endl;

    exit(ERRNUM_NO_CONFIG);
  };

  return res;
}
