#pragma once

#include "../lua/config.hpp"

#include <gtkmm.h>
#include <vector>

namespace Iris
{

class Row : public Gtk::Widget
{
private:
  Gtk::Label title_;
  Gtk::Box box_;
  std::vector<Gtk::Button *> vPButton_;

public:
  Row();
  Row(Iris::Config::Row const &_row);

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};
} // namespace Iris
