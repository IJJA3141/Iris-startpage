#ifndef _IRIS_CONFIG_LOADER
#define _IRIS_CONFIG_LOADER
#include "debugger.hpp"

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

struct Config {
public:
  struct Button {
    int buttonIndex;
    int pageIndex;
    int row;

    std::string name;
    std::string image;

    void func();
  };

  struct Row {
    std::string title;
    std::vector<Iris::Config::Button> vButton;
  };

  struct Page {
    std::string name;
    std::string image;
    Iris::Config::Row aRow[3];
  };

public:
  float width;
  float height;
  float image_width;
  bool use_local;

  std::vector<Iris::Config::Page> vPage;
};

class ConfigRetriever
{
private:
  static Iris::ConfigRetriever *pConfig_;
  lua_State *L_;
  Iris::Debugger deb_;

public:
  static Iris::ConfigRetriever *get_config_retriver();
  Iris::Config config;

  void call_function(int _page_index, int _row, int _index);

private:
  ConfigRetriever();
  ~ConfigRetriever();

  // _tableIndex should start at -2
  // but i'm to lazy to change it
  bool get_bool(std::string _name, int _tableIndex = 1);
  float get_float(std::string _name, int _tableIndexe = 1);
  std::string get_string(std::string _name, int _tableIndexe = 1, bool _handle_error = false);
  std::vector<Iris::Config::Button> iterate_table();

public:
  ConfigRetriever(Iris::ConfigRetriever &_other) = delete;
  void operator=(const Iris::ConfigRetriever &) = delete;
};

}; // namespace Iris

#endif // !_IRIS_CONFIG_LOADER
