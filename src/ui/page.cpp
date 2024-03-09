#include "page.hpp"

#include "../EXAMPLE_CONFIG.hpp"

Iris::Page::Page() : picture_(_IRIS_EXAMPLE_CONFIG_IMAGE_PATH), search_()
{
  // css class asignation
  this->picture_.set_name("pic");
  this->search_.set_name("search");

  // parenting
  this->picture_.set_parent(*this);
  this->search_.set_parent(*this);

  // settings
  this->set_focusable(false);
  this->picture_.set_focusable(false);

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
  Gtk::Allocation pic, search;

  pic.set_x(0);
  pic.set_width(_IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);

  pic.set_y(0);
  pic.set_height(_height);

  search.set_x(_IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);
  search.set_width(_width - _IRIS_EXAMPLE_CONFIG_IMAGE_WIDTH);

  search.set_y(0);
  search.set_height(_height);

  this->picture_.size_allocate(pic, _baseline);
  this->search_.size_allocate(search, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Page::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
