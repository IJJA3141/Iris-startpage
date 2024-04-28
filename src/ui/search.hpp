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
  Gtk::Box searchBox_;
  Gtk::Label leftLabel_;
  Gtk::Entry entry_;
  Gtk::Label rightLabel_;

  Gtk::Box entryBox_;
  std::vector<Iris::Entry> vEntry_;
  std::vector<std::pair<int, Iris::Entry *>> pMatchingEntry_;
  int index_;
  uint entryNumber_;
  std::vector<Gtk::Label*> vPLabel_;

public:
  Search();

  void size_allocate_vfunc(int _width, int _height, int _baseline) override;

private:
  void match(const std::string _input);
  void show_entrys();
};
} // namespace Iris
