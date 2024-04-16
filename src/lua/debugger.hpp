#pragma once

extern "C" {
#include <lua.h>
}

#include <cstdint>
#include <string>

namespace Iris
{

class Debugger
{
public:
  uint8_t depth;

public:
  // indexing start at 1 as lua does
  // 0 will print all the stack
  Debugger(lua_State *const _L = nullptr, const uint8_t _depth = 0);

  void set_stack(lua_State *const _L);
  void print_stack();

private:
  lua_State *L_;
  std::string str_;
  uint8_t currentDepth_;

private:
  void print_item(const int8_t _index, const bool _as_key);
  void print_table(int8_t _index);
  void print();
};

} // namespace Iris
