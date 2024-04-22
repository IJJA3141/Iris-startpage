#pragma once

#include <gtkmm.h>

namespace Iris
{
class Window : public Gtk::Window
{
public:
  Window();

  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
};

} // namespace Iris
