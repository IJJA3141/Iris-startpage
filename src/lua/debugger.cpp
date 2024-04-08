#include "debugger.hpp"

#include <iostream>
#include <lua.h>

Iris::Debugger::Debugger(lua_State *const _L) : L_(_L) { return; };
void Iris::Debugger::set_stack(lua_State *const _L)
{
  this->L_ = _L;

  return;
};

void Iris::Debugger::print_stack(int _r)
{
  if (this->L_ == nullptr) {
    std::cout << "debugger wasn't initialized !" << std::endl;
    exit(1);
  }

  this->r_ = 0;
  this->str_ = "-- Stack from top to bottom\n";
  this->max_r_ = _r;

  int n = lua_gettop(this->L_);

  if (n == 0) {
    this->str_ += "<empty>";
    this->print();

    return;
  };

  for (int i = 1; i <= n; i++) {
    this->str_ += " ";

    this->print_item(i, false);
    this->str_ += "\n";
  }

  this->print();

  return;
}

void Iris::Debugger::print_item(int _index, bool _as_key)
{
  int type = lua_type(this->L_, _index);

  switch (type) {
  case LUA_TNIL:
    if (!_as_key) this->str_ += '"';
    this->str_ += "nil";
    if (!_as_key) this->str_ += '"';
    break;

  case LUA_TNUMBER:
    this->str_ += std::to_string((float)lua_tonumber(this->L_, _index));
    break;

  case LUA_TBOOLEAN:
    if (lua_toboolean(this->L_, _index))
      this->str_ += "true";
    else
      this->str_ += "false";
    break;

  case LUA_TSTRING:
    if (!_as_key) this->str_ += '"';
    this->str_ += lua_tostring(this->L_, _index);
    if (!_as_key) this->str_ += '"';
    break;

  case LUA_TTABLE:
    if (this->max_r_ == -1) {
      this->print_table(_index);
      break;
    };

    if (this->max_r_ > this->r_) {
      this->print_table(_index);
    } else
      this->str_ += "\"{...}\"";
    break;

  case LUA_TFUNCTION:
    if (!_as_key) this->str_ += '"';
    this->str_ += "function()";
    if (!_as_key) this->str_ += '"';
    break;

  default:
    if (!_as_key) this->str_ += '"';
    std::cout << "???" << std::endl;
    if (!_as_key) this->str_ += '"';
    break;
  }

  return;
};

void Iris::Debugger::print_table(int _index)
{
  if (_index < 0) _index = lua_gettop(this->L_);

  this->r_++;
  const char *pre = "{";

  if (this->is_seq(_index))
    this->print_seq(_index);
  else {
    lua_pushnil(this->L_);

    while (lua_next(this->L_, _index)) {
      this->str_ += pre;

      this->print_item(-2, true);

      this->str_ += " = ";
      this->print_item(-1, false);

      lua_pop(this->L_, 1);

      pre = ", ";
    }

    this->str_ += "}";
    this->r_--;
  }

  return;
}

bool Iris::Debugger::is_seq(int _index)
{
  lua_pushnil(this->L_);

  int keynum = 1;

  while (lua_next(this->L_, _index)) {
    lua_rawgeti(this->L_, _index, keynum);

    if (lua_isnil(this->L_, -1)) {
      lua_pop(this->L_, 3);

      return false;
    }

    lua_pop(this->L_, 2);

    keynum++;
  }

  return true;
}

void Iris::Debugger::print_seq(int _index)
{
  this->str_ += "{";

  for (int k = 1;; k++) {
    lua_rawgeti(this->L_, _index, k);

    if (lua_isnil(this->L_, -1)) break;
    if (k > 1) this->str_ += ", ";

    this->print_item(-1, false);
    lua_pop(this->L_, 1);
  }

  lua_pop(this->L_, 1);
  this->str_ += "}";

  return;
}

void Iris::Debugger::print()
{
  std::cout << this->str_ << std::endl;

  return;
}
