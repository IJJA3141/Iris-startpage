#pragma once

#include "../lua/config.hpp"

#include <gtkmm.h>
#include <string>
#include <utility>
#include <vector>

namespace Iris
{
class Search : public Gtk::Widget
{
private:
  Gtk::Label rightLabel_;
  Gtk::Label leftLabel_;
  Gtk::Box searchBox_;
  Gtk::Entry entry_;

  std::vector<std::pair<int, Iris::Entry *>> pMatchingEntry_;
  std::vector<Gtk::Label *> vPLabel_;
  std::vector<Iris::Entry> vEntry_;
  Gtk::Box entryBox_;
  uint entryNumber_;
  int index_;

public:
  Search();
  void grab_focus();
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;

private:
  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
  void match();
  void show_entrys();
};
} // namespace Iris
