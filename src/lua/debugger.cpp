#include "debugger.hpp"
#include "../const/error.hpp"

#include <cstdint>
#include <iostream>
#include <lua.h>
#include <string>

Iris::Debugger::Debugger(lua_State *const _L, const uint8_t _depth)
    : L_(_L), depth(_depth), currentDepth_(1)
{
  return;
};

void Iris::Debugger::set_stack(lua_State *const _L)
{
  this->L_ = _L;
  return;
}

void Iris::Debugger::print_stack()
{
  if (this->L_ == nullptr) {
    std::cout << DEBUGGER_UNINITIALIZED << std::endl;
    exit(1);
  }

  this->currentDepth_ = 1;
  this->str_ = "-- Lua stack\n";

  int n = lua_gettop(this->L_);

  if (n == 0) {
    this->str_ += "<empty>";
    this->print();

    return;
  }

  for (uint8_t i = n; i >= 1; i--) {
    this->str_ += " ";

    this->print_item(i, false);
    this->str_ += "\n";
  }

  this->print();
  return;
}

void Iris::Debugger::print_item(const int8_t _index, bool const _as_key)
{
  int type = lua_type(this->L_, _index);

  switch (type) {
  case LUA_TNUMBER:
    this->str_ += std::to_string((float)lua_tonumber(this->L_, _index));
    break;

  case LUA_TBOOLEAN:
    if (lua_toboolean(this->L_, _index))
      this->str_ += "true";
    else
      this->str_ += "false";
    break;

  case LUA_TTABLE:
    if (this->depth == 0 || this->depth >= this->currentDepth_)
      this->print_table(_index);
    else
      this->str_ += "\"{...}\"";
    break;

  default:
    if (!_as_key) this->str_ += '"';

    switch (type) {
    case LUA_TNIL:
      this->str_ += "nil";
      break;

    case LUA_TSTRING:
      this->str_ += lua_tostring(this->L_, _index);
      break;

    case LUA_TFUNCTION:
      this->str_ += "function()";
      break;

    default:
      this->str_ += "???";
    }

    if (!_as_key) this->str_ += '"';
  }

  return;
}

void Iris::Debugger::print_table(int8_t _index)
{
  if (_index < 0) _index = lua_gettop(this->L_);

  this->currentDepth_++;
  lua_pushnil(this->L_);
  this->str_ += "{";

  while (lua_next(this->L_, _index)) {
    if (lua_isnumber(this->L_, -2)) {
      this->print_item(-1, false);
      //} else if (lua_isnil(this->L_, _index)) {
      //  break;
    } else {
      this->print_item(-2, true);
      this->str_ += " = ";
      this->print_item(-1, false);
    }

    lua_pop(this->L_, 1);
    this->str_ += ", ";
  }

  this->str_ += "}";
  this->currentDepth_--;

  return;
}

void Iris::Debugger::print()
{
  std::cout << this->str_ << std::endl;
  return;
}
