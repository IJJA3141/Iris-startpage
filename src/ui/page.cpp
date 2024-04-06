#include "./page.hpp"

Iris::Page::Page() { return; }

Iris::Page::Page(Iris::Config::Page const &_page)
    : picture_(_page.image), box_(Gtk::Orientation::VERTICAL), title_(_page.name)
{
  for (int i = 0; i < 3; i++) {
    this->aRow_[i] = Iris::Row(_page.aRow[i]);
    this->box_.append(this->aRow_[i]);
  }

  this->picture_.set_parent(*this);
  this->box_.set_parent(*this);

  this->picture_.set_size_request(1, 1);

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
  Gtk::Allocation picture, box;

  picture.set_height(_height);
  picture.set_width(Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  picture.set_x(0);
  picture.set_y(0);

  box.set_height(_height);
  box.set_width(_width - Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  box.set_x(Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  box.set_y(0);

  this->picture_.size_allocate(picture, _baseline);
  this->box_.size_allocate(box, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Page::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
