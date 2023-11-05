#ifndef LOADER

#include <fstream>
#include <iostream>
#include <json/json.h>
#include <string>
#include <sys/stat.h>

#include "macros.hpp"

#define LOADER

namespace Iris {

extern std::string HOME_DIR;

// Caller get ownership of the response
Json::Value *load_condifg();
bool file_exist(std::string _file);

} // namespace Iris

#endif // !LOADER
