#pragma once

extern "C" {
#include <lua.hpp>
}

#include <string>

namespace Iris
{

class Debugger
{
private:
  lua_State *L_;
  std::string str_;
  int r_;
  int max_r_;

public:
  Debugger(lua_State *const _L = nullptr);

  void set_stack(lua_State *const _L);
  void print_stack(int _r = -1);

private:
  void print_item(int _index, bool _as_key);
  void print_table(int _index);
  bool is_seq(int _index);
  void print_seq(int _index);
  void print();
};

} // namespace Iris
