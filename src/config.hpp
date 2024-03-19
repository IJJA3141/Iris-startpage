#ifndef _IRIS_CONFIG_LOADER

#include <string>
#include <utility>
#include <vector>

extern "C" {
#include <lua.hpp>
}

namespace Iris
{
namespace xdg // fetch the xdg application
{
std::vector<std::pair<std::string, std::string>> fetch();
};

// Singleton for config
//
// read values
// call functions
class Config
{
private:
  static Iris::Config *pConfig_;
  lua_State *L_;

public:
  static Iris::Config *get_config();

  bool get_bool_value(const std::string _name);
  void get_table_value(const std::string _name);
  float get_float_value(const std::string _name);
  std::string get_string_value(const std::string _name);

  void call_function(const std::string _name);

private:
  Config();
  ~Config();

public:
  Config(Iris::Config &_other) = delete;
  void operator=(const Iris::Config &) = delete;
};

}; // namespace Iris

#endif // !_IRIS_CONFIG_LOADER
