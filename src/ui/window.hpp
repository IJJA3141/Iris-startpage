#pragma once

#include "page.hpp"
#include "search.hpp"
#include <gtkmm.h>

namespace Iris
{
class Window : public Gtk::Window
{
private:
  Iris::Search search_;
  Iris::Page page_;

public:
  Window();

  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
};

} // namespace Iris
