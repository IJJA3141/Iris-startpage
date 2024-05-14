#pragma once

#include <gtkmm.h>

#include "../lua/config.hpp"

namespace Iris
{

class Row : public Gtk::Widget
{
private:
  Gtk::Label title_;
  Gtk::Box box_;
  std::vector<Gtk::Button *> vPButton_;

public:
  Row(const Iris::Config::Row &_row);

  void size_allocate_vfunc(int width, int height, int baseline) override;
};

class Page : public Gtk::Widget
{
private:
  Iris::Row *aRow_[3];
  Gtk::Label title_;
  Gtk::Box box_;

public:
  Page(const Iris::Config::Page &_page);

  void size_allocate_vfunc(int width, int height, int baseline) override;

private:
};

} // namespace Iris
