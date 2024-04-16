#pragma once

#include "debugger.hpp"

extern "C" {
#include <lua.hpp>
}

#include <string>
#include <vector>

namespace Iris
{
namespace xdg
{

std::vector<std::pair<std::string, std::string>> fetch();

} // namespace xdg

namespace Config
{

struct Button {
  int page_id;
  int row_id;
  int button_id;

  std::string label;
  std::string image;
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

struct Config {
  int width;
  int height;
  int image_width;
  bool use_local;
  bool is_overlay;

  std::vector<Iris::Config::Page> vPage;
};

} // namespace Config

class ConfigRetriever
{
public:
  Iris::Config::Config config;

private:
  static Iris::ConfigRetriever *pConfig_;
  Iris::Debugger debugger_;
  lua_State *L_;

public:
  static Iris::ConfigRetriever *get_config_retriver();

  void call_function(int _page_id, int _row_id, int _button_id);
  void debug_config();

private:
  ConfigRetriever();

  bool get_bool(std::string _name, int _tableIndex = -2);
  float get_float(std::string _name, int _tableIndex = -2);
  std::string get_string(std::string _name, int _tableIndex = -2, bool _handle_error = false);
  std::vector<Iris::Config::Button> iterate_table(int _page_id, int _row_id);

private:
  ConfigRetriever(Iris::ConfigRetriever &_other) = delete;
  void operator=(const Iris::ConfigRetriever &) = delete;
};

} // namespace Iris
