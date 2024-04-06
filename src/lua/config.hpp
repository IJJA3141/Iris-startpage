#pragma once

extern "C" {
#include <lua.hpp>
}

#include <string>
#include <vector>

namespace Iris
{
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

  std::vector<Iris::Config::Page> vPage;
};

} // namespace Config

class ConfigRetriever
{
public:
  Iris::Config::Config config;

private:
  static Iris::ConfigRetriever *pConfig_;
  lua_State *L_;

public:
  static Iris::ConfigRetriever *get_config_retriver();

  void call_function(int _page_id, int _row_id, int _button_id);

private:
  ConfigRetriever();

public:
  ConfigRetriever(Iris::ConfigRetriever &_other) = delete;
  void operator=(const Iris::ConfigRetriever &) = delete;
};

}; // namespace Iris
