#include "image.hpp"

Up::Image::Image() {
  this->set_expand(true);

  this->padding_.set_left(5); // left right top bottom
  padding_.set_right(15);
  padding_.set_top(20);
  padding_.set_bottom(2);

  this->set_name("image");

  return;
}

Up::Image::~Image(){};

Gtk::SizeRequestMode Up::Image::get_request_mode_vfunc() const {
  return Gtk::Widget::get_request_mode_vfunc();
}

void Up::Image::measure_vfunc(Gtk::Orientation _orientation,
                              int /* _for_size */, int &_min, int &_natural,
                              int &_min_baseline,
                              int &_natural_baseline) const {

  if (_orientation == Gtk::Orientation::HORIZONTAL) {
    _min = 60;
    _natural = 100;
  } else {
    _min = 50;
    _natural = 70;
  }

  _min_baseline = -1;
  _natural_baseline = -1;

  return;
};

void Up::Image::on_map() {
  Gtk::Widget::on_map();
  return;
}

void Up::Image::on_unmap() {
  Gtk::Widget::on_unmap();
  return;
}
void Up::Image::on_realize() {
  Gtk::Widget::on_realize();
  return;
};
void Up::Image::on_unrealize() {
  Gtk::Widget::on_unrealize();
  return;
};

void Up::Image::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &snapshot) {
  const Gdk::Rectangle allocation = get_allocation();
  const Gdk::Rectangle rect(0, 0, allocation.get_width(),
                            allocation.get_height());

  auto cr = snapshot->append_cairo(rect);

  Gdk::Cairo::set_source_rgba(cr, bg_);
  cr->fill();

  return;
};
