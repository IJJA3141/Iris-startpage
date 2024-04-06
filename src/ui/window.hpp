#pragma once

#include "page.hpp"

#include <gdkmm.h>
#include <glibmm.h>
#include <gtkmm.h>

namespace Iris
{
class Window : public Gtk::Window
{
private:
  Gtk::Stack stack_;
  std::vector<Iris::Page *> vPPage_;
  Gtk::Label search_;

  bool search_is_on_;
  int index_;

public:
  Window();

  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;

private:
  void swap_search();

private:
  void operator++();
  void operator--();
};
} // namespace Iris
