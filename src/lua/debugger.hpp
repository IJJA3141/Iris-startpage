#ifndef _IRIS_LUA_DEBUGGER
#define _IRIS_LUA_DEBUGGER

#include <string>

extern "C" {
#include <lua.hpp>
}

namespace Iris
{
class Debugger
{
private:
  lua_State *L_;
  std::string str_;

public:
  Debugger(lua_State *_L = nullptr);

  void set_stack(lua_State *_L);
  void print_stack();

private:
  void print_item(int _index, bool _as_key);
  void print_table(int _index);
  bool is_seq(int _index);
  void print_seq(int _index);
  void print();
};

} // namespace Iris

#endif //!_IRIS_LUA_DEBUGGER
