#pragma once

#include "row.hpp"

#include <gtkmm.h>

namespace Iris
{
class Page : public Gtk::Widget
{
private:
  Gtk::Label title_;
  Gtk::Picture picture_;
  Gtk::Box box_;
  Iris::Row aRow_[3];

public:
  Page();
  Page(Iris::Config::Page const &_page);

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};

}; // namespace Iris
