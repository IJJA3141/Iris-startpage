#include "config.hpp"

#include <cstdlib>
#include <iostream>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

Iris::Config *Iris::Config::pConfig_ = nullptr;

Iris::Config *Iris::Config::get_config()
{
  if (Iris::Config::pConfig_ == nullptr) Iris::Config::pConfig_ = new Iris::Config();

  return Iris::Config::pConfig_;
}

Iris::Config::Config() : vPage()
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

  this->deb_.print_stack();

  this->width = this->get_float("width");
  exit(1);
  this->height = this->get_float("height");
  this->image_width = this->get_float("image_width");
  this->use_local = this->get_bool("use_local");

  lua_getglobal(this->L_, "pages");
  if (!lua_istable(this->L_, -1)) {
    std::cout << "pages must be a table" << std::endl;
    exit(1);
  }

  return;
}

Iris::Config::~Config()
{
  lua_close(this->L_);
  return;
}

bool Iris::Config::get_bool(std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());
  if (!lua_isboolean(this->L_, -1)) {
    std::cout << _name << " must be a boolean" << std::endl;
    exit(1);
  }

  this->deb_.print_stack();

  return lua_toboolean(this->L_, -1);
};

float Iris::Config::get_float(std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());
  if (!lua_isnumber(this->L_, -1)) {
    std::cout << _name << " must be a number" << std::endl;
    exit(1);
  }

  this->deb_.print_stack();

  return lua_tonumber(this->L_, -1);
};

std::string Iris::Config::get_string(std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());
  if (!lua_isstring(this->L_, -1)) {
    std::cout << _name << " must be a string" << std::endl;
    exit(1);
  }

  this->deb_.print_stack();

  return lua_tostring(this->L_, -1);
};
