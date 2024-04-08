#include "config.hpp"
#include "../error.hpp"

#include <iostream>
#include <lua.h>
#include <string>

std::string a[3] = {"top_button", "center_button", "bottom_button"};

Iris::ConfigRetriever *Iris::ConfigRetriever::pConfig_ = nullptr;

Iris::ConfigRetriever *Iris::ConfigRetriever::get_config_retriver()
{
  if (Iris::ConfigRetriever::pConfig_ == nullptr)
    Iris::ConfigRetriever::pConfig_ = new Iris::ConfigRetriever();

  return Iris::ConfigRetriever::pConfig_;
}

Iris::ConfigRetriever::ConfigRetriever()
{
  this->L_ = luaL_newstate();
  luaL_openlibs(this->L_);

  int err = luaL_dofile(this->L_, "/etc/iris/config.lua");

  if (err != LUA_OK) {
    std::cout << lua_tostring(this->L_, -1) << std::endl;
    exit(1);
  }

  this->debugger_.set_stack(this->L_);
  lua_getglobal(this->L_, "Config");

  this->config.image_width = this->get_float("image_width");
  this->config.width = this->get_float("width");
  this->config.height = this->get_float("height");
  this->config.use_local = this->get_bool("use_local");
  this->config.is_overlay = this->get_bool("is_overlay");

  lua_pushstring(this->L_, "pages");
  lua_gettable(this->L_, 1);

  if (!lua_istable(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG << std::endl;
    exit(1);
  }

  lua_remove(this->L_, 1);

  size_t tableSize = lua_rawlen(this->L_, 1);
  // for f*ck's sake one based indexing
  for (int i = 1; i <= tableSize; i++) {
    Iris::Config::Page page;

    lua_rawgeti(this->L_, 1, i);

    page.name = this->get_string("name");
    page.image = this->get_string("image");

    for (int i = 0; i < 3; i++) {
      lua_pushstring(this->L_, a[i].c_str());
      lua_gettable(this->L_, 2);

      page.aRow[i].title = this->get_string("title", -2, true);

      lua_pushstring(this->L_, "buttons");
      lua_gettable(this->L_, -2);

      page.aRow[i].vButton = this->iterate_table();

      lua_remove(this->L_, -1);
      lua_remove(this->L_, -1);
    }

    this->config.vPage.push_back(page);
    lua_remove(this->L_, -1);
  }

  return;
}

bool Iris::ConfigRetriever::get_bool(std::string _name, int _tableIndex)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);

  if (!lua_isboolean(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG_BOOLEAN(_name) << std::endl;
    exit(1);
  }

  bool r = lua_toboolean(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

float Iris::ConfigRetriever::get_float(std::string _name, int _tableIndex)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);
  if (!lua_isnumber(this->L_, -1)) {
    std::cout << ERROR_LUA_CONFIG_NUMBER(_name) << std::endl;
    exit(1);
  }

  float r = lua_tonumber(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

std::string Iris::ConfigRetriever::get_string(std::string _name, int _tableIndex,
                                              bool _handle_error)
{
  std::string r = "";

  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndex);

  if (!lua_isstring(this->L_, -1)) {
    if (!_handle_error) {
      std::cout << ERROR_LUA_CONFIG_STRING(_name) << std::endl;
      exit(1);
    }

    lua_remove(this->L_, -1);
    return r;
  }

  r = lua_tostring(this->L_, -1);
  lua_remove(this->L_, -1);

  return r;
}

std::vector<Iris::Config::Button> Iris::ConfigRetriever::iterate_table()
{
  std::vector<Iris::Config::Button> r = {};

  int tableSize = lua_rawlen(this->L_, -1);
  for (int i = 1; i <= tableSize; i++) {
    Iris::Config::Button button;

    lua_rawgeti(this->L_, -1, i);

    button.label = this->get_string("label");
    button.image = this->get_string("image");

    r.push_back(button);
    lua_remove(this->L_, -1);
  }

  return r;
}

void Iris::ConfigRetriever::call_function(int _page_id, int _row_id, int _button_id)
{
  std::cout << "Page: " << _page_id << "\nRow: " << _row_id << "\nButton: " << _button_id
            << std::endl;

  return;
};

void Iris::ConfigRetriever::debugg_config()
{
  std::string str = "-- Config\n";

  str += "{ width = ";
  str += std::to_string(this->config.width);
  str += ", height = ";
  str += std::to_string(this->config.height);
  str += ", image_width = ";
  str += std::to_string(this->config.image_width);
  str += ", use_local = ";

  if (this->config.use_local)
    str += "true";
  else
    str += "flase";

  str += ", pages = {";
  for (Iris::Config::Page _ : this->config.vPage) {
    str += "{ name = ";
    str += _.name;
    str += ", image = ";
    str += _.image;

    for (int i = 0; i < 2; i++) {
      str += ", ";
      str += a[i];
      str += "= { title = ";
      str += _.aRow[i].title;
      str += ", buttons = {";

      for (Iris::Config::Button __ : _.aRow[i].vButton) {
        str += "{ label = ";
        str += __.label;
        str += ", image = ";
        str += __.image;
        str += ", cmd = 'func', }";
      }

      str += "}";
    }

    str += "},";
  }
  str += "}";

  std::cout << str << std::endl;

  return;
};
