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

Iris::Config::Config()
{
  this->L_ = luaL_newstate();
  luaL_openlibs(this->L_);

  int err = luaL_dofile(this->L_, "/etc/iris/config.lua");

  if (err != LUA_OK) {
    std::cout << lua_tostring(this->L_, -1) << std::endl;
    exit(1);
  }

  return;
}

Iris::Config::~Config()
{
  lua_close(this->L_);
  return;
}

bool Iris::Config::get_bool_value(const std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());

  if (lua_isboolean(this->L_, -1)) return (bool)lua_toboolean(this->L_, -1);

  return false;
}

float Iris::Config::get_float_value(const std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());

  if (lua_isnumber(this->L_, -1)) return (float)lua_tonumber(this->L_, -1);

  return 0.0;
}

std::string Iris::Config::get_string_value(const std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());

  if (lua_isstring(this->L_, -1)) return (std::string)lua_tostring(this->L_, -1);

  return "";
}

void Iris::Config::get_table_value(const std::string _name){};

void Iris::Config::call_function(const std::string _name)
{
  lua_getglobal(this->L_, _name.c_str());

  if (lua_isfunction(this->L_, -1) && lua_pcall(this->L_, 0, 0, 0) == LUA_OK) return;

  std::cout << "function error " << lua_tostring(this->L_, -1) << std::endl;

  return;
}
