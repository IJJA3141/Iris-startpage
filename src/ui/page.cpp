#include "page.hpp"

#include "../EXAMPLE_CONFIG.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include <string>

Iris::Page::Page() : picture_(_IRIS_EXAMPLE_CONFIG_IMAGE_PATH), box_(Gtk::Orientation::VERTICAL)
{
  // css class asignation
  this->picture_.set_name("test");
  this->box_.set_name("box");

  // parenting
  this->picture_.set_parent(*this);
  this->box_.set_parent(*this);

  this->box_.append(this->entry_);
  this->box_.append(this->scrolledWindo_);

  auto a = new Gtk::Box(Gtk::Orientation::VERTICAL);
  this->scrolledWindo_.set_child(*a);

  for (int i = 0; i < 500; i++)
    a->append(*new Gtk::Label(std::to_string(i)));

  // settings
  this->scrolledWindo_.set_expand(true);

  return;
}

void Iris::Page::measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum,
                               int &_natural, int &_minimum_baseline, int &_natural_baseline) const
{
  _minimum_baseline = -1;
  _natural = 0;
  _minimum = 0;

  return;
}

void Iris::Page::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation box, pic;

  pic.set_x(0);
  pic.set_width(_IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);

  pic.set_y(0);
  pic.set_height(_height);

  box.set_x(_IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);
  box.set_width(_width - _IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);

  box.set_y(0);
  box.set_height(_height);

  this->picture_.size_allocate(pic, _baseline);
  this->box_.size_allocate(box, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Page::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
