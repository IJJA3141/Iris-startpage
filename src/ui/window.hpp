#ifndef _IRIS_WINDOW
#define _IRIS_WINDOW

#include "page.hpp"

#include <gtkmm.h>
#include <vector>

namespace Iris
{
class Window : public Gtk::Window
{
private:
  Iris::Page pg;
  Iris::Page pg2;
  Gtk::Stack stack_;

  // std::vector<Iris::Page *> vPPage_;

public:
  Window();

  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
};
} // namespace Iris

#endif // !_IRIS_WINDOW
