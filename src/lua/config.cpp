#include "config.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

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

  this->deb_.set_stack(this->L_);
  lua_getglobal(this->L_, "Config");

  this->config_.image_width = this->get_float("image_width");
  this->config_.width = this->get_float("width");
  this->config_.height = this->get_float("height");
  this->config_.use_local = this->get_bool("use_local");

  lua_pushstring(this->L_, "pages");
  lua_gettable(this->L_, 1);

  if (!lua_istable(this->L_, -1)) {
    std::cout << "config error !\npages must be a table\nAborting..." << std::endl;
    exit(1);
  }

  lua_remove(this->L_, 1);

  // one based indexing !
  size_t tableSize = lua_rawlen(this->L_, 1);
  for (int i = 1; i <= tableSize; i++) {
    Iris::Config::Page page;

    lua_rawgeti(this->L_, 1, i);

    page.name = this->get_string("name", 2);
    page.image = this->get_string("image", 2);

    lua_pushstring(this->L_, "top_button");
    lua_gettable(this->L_, 2);

    if (!lua_istable(this->L_, -1)) {
      std::cout << "config error !\ntop_button must be a table\nAborting..." << std::endl;
      exit(1);
    }

    size_t buttonTableSize = lua_rawlen(this->L_, 1);
    for (int j = 1; j <= buttonTableSize; j++) {
      Iris::Config::Button button;

      lua_rawgeti(this->L_, 1, j);

      button.image = this->get_string("image", 4);
      std::cout << "-- j:" << j << " i:" << i << std::endl;
      this->deb_.print_stack();
      button.name = this->get_string("label", 4);
      button.index = j;
      button.page_index = i;

      page.aVButton[0].push_back(button);

      lua_remove(this->L_, -1);
    }
    lua_remove(this->L_, -1);

    lua_pushstring(this->L_, "center_button");
    lua_gettable(this->L_, 2);

    if (!lua_istable(this->L_, -1)) {
      std::cout << "config error !\ntop_button must be a table\nAborting..." << std::endl;
      exit(1);
    }

    buttonTableSize = lua_rawlen(this->L_, 1);
    for (int j = 1; j <= buttonTableSize; j++) {
      Iris::Config::Button button;

      lua_rawgeti(this->L_, 1, j);

      button.image = this->get_string("image", 4);
      button.name = this->get_string("label", 4);
      button.index = j;
      button.page_index = i;

      page.aVButton[0].push_back(button);

      lua_remove(this->L_, -1);
    }
    lua_remove(this->L_, -1);

    lua_pushstring(this->L_, "bottom_button");
    lua_gettable(this->L_, 2);

    if (!lua_istable(this->L_, -1)) {
      std::cout << "config error !\ntop_button must be a table\nAborting..." << std::endl;
      exit(1);
    }

    buttonTableSize = lua_rawlen(this->L_, 1);
    for (int j = 1; j <= buttonTableSize; j++) {
      Iris::Config::Button button;

      lua_rawgeti(this->L_, 1, j);

      button.image = this->get_string("image", 4);
      button.name = this->get_string("label", 4);
      button.index = j;
      button.page_index = i;

      page.aVButton[0].push_back(button);

      lua_remove(this->L_, -1);
    }
    lua_remove(this->L_, -1);

    lua_remove(this->L_, -1);
  }

  return;
}

Iris::Config *Iris::ConfigRetriever::get_config() { return &this->config_; };

Iris::ConfigRetriever::~ConfigRetriever()
{
  lua_close(this->L_);
  return;
}

bool Iris::ConfigRetriever::get_bool(std::string _name, int _tableIndexe)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndexe);

  if (!lua_isboolean(this->L_, -1)) {
    std::cout << "config error !\n" << _name << " must be a boolean\nAborting..." << std::endl;
    exit(1);
  }

  bool r = lua_toboolean(this->L_, -1);

  lua_remove(this->L_, -1);

  return r;
}

float Iris::ConfigRetriever::get_float(std::string _name, int _tableIndexe)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndexe);

  if (!lua_isnumber(this->L_, -1)) {
    std::cout << "config error !\n" << _name << " must be a number\nAborting..." << std::endl;
    exit(1);
  }

  float r = lua_tonumber(this->L_, -1);

  lua_remove(this->L_, -1);

  return r;
}

std::string Iris::ConfigRetriever::get_string(std::string _name, int _tableIndexe)
{
  lua_pushstring(this->L_, _name.c_str());
  lua_gettable(this->L_, _tableIndexe);

  if (!lua_isstring(this->L_, -1)) {
    std::cout << "config error !\n" << _name << " must be a string\nAborting..." << std::endl;
    exit(1);
  }

  std::string r = lua_tostring(this->L_, -1);

  lua_remove(this->L_, -1);

  return r;
}
