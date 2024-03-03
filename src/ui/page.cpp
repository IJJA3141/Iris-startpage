#include "page.hpp"

#include <iostream>

#include "../EXAMPLE_CONFIG.hpp"
#include "gtkmm/enums.h"

Iris::Page::Page()
    : image_(IMAGE_PATH), box_(Gtk::Orientation::HORIZONTAL),
      lg_("jfjjjfjjfjfjfjfjffffffffdskafkdsajf;")
{
  this->image_.set_name("stack");
  this->box_.set_name("box");
  this->box_.append(this->lg_);

  this->image_.set_parent(*this);
  this->box_.set_parent(*this);

  return;
}

void Iris::Page::measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum,
                               int &_natural, int &_minimum_baseline, int &_natural_baseline) const
{
  _minimum_baseline = -1;
  _minimum = WIDTH;
  _natural = WIDTH;

  return;
}

void Iris::Page::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation child_allocation_one;
  Gtk::Allocation child_allocation_two;

  child_allocation_one.set_x(0);
  child_allocation_one.set_y(0);

  child_allocation_one.set_height(_height);
  child_allocation_one.set_width(_width - 1200);

  child_allocation_two.set_y(0);
  child_allocation_two.set_x(_width - 1200);

  child_allocation_two.set_width(1200);
  child_allocation_two.set_height(_height);

  this->box_.size_allocate(child_allocation_two, _baseline);
  this->image_.size_allocate(child_allocation_one, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Page::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
