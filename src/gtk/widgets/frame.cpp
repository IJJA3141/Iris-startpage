#include "frame.hpp"

Iris::Frame::Frame() : img_("/home/alexe/.config/iris/cbg-10.gif") {
  this->set_name("frame");

  return;
}

Iris::Frame::~Frame(){};

Gtk::SizeRequestMode Iris::Frame::get_request_mode_vfunc() const {
  // Accept the default value supplied by the base class.
  return Gtk::Widget::get_request_mode_vfunc();
}

// Discover the total amount of minimum space and natural space needed by
// this widget.
// Let's make this simple example widget always need minimum 60 by 50 and
// natural 100 by 70.
void Iris::Frame::measure_vfunc(Gtk::Orientation _orientation, int _for_size,
                                int &_min, int &_natural, int &_min_baseline,
                                int &_natural_baseline) const {
  if (_orientation == Gtk::Orientation::HORIZONTAL) {
    _min = 60;
    _natural = 100;
  } else {
    _min = 50;
    _natural = 70;
  }

  // Don't use baseline alignment.
  _min_baseline = -1;
  _natural_baseline = -1;
}

void Iris::Frame::on_map() {
  // Call base class:
  Gtk::Widget::on_map();
}

void Iris::Frame::on_unmap() {
  // Call base class:
  Gtk::Widget::on_unmap();
}

void Iris::Frame::on_realize() { Gtk::Widget::on_realize(); }

void Iris::Frame::on_unrealize() {
  // Call base class:
  Gtk::Widget::on_unrealize();
}
