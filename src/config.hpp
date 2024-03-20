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

struct Page {
};

// Singleton for config
//
// read values
// call functions
class Config
{
public:
  struct Button {
    std::string name;
    std::string image;
    int page_index;
    int index;
  };

  struct Page {
    std::string name;
    std::string image;
    std::vector<Iris::Config::Button> aVButton[3];
  };

private:
  static Iris::Config *pConfig_;
  lua_State *L_;

public:
  float width;
  float height;
  float image_width;
  bool use_local;

  std::vector<Iris::Config::Page> vPage;

public:
  static Iris::Config *get_config();

  void call_function(int _page_index, int _index);

private:
  Config();
  ~Config();

  bool get_bool(std::string _name);
  float get_float(std::string _name);
  std::string get_string(std::string _name);

  void debug_stack();

public:
  Config(Iris::Config &_other) = delete;
  void operator=(const Iris::Config &) = delete;
};

}; // namespace Iris

#endif // !_IRIS_CONFIG_LOADER
