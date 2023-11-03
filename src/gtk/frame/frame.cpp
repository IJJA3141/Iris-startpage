#include "frame.hpp"
#include "gdkmm/general.h"
#include "gdkmm/rectangle.h"
#include "gtkmm/enums.h"
#include "gtkmm/widget.h"
#include <gtkmm.h>

Up::Frame::Frame() {
  this->set_expand(true);

  this->padding_.set_left(5); // left right top bottom
  padding_.set_right(15);
  padding_.set_top(20);
  padding_.set_bottom(2);
  
  std::string homedir;
  if ((homedir = Glib::getenv("HOME")) == "") {
  }

  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  css_provider->load_from_path(homedir + "/.config/Up/style.css");

 this->set_name("test"); 
  this->get_style_context()->add_provider(css_provider,
                                          GTK_STYLE_PROVIDER_PRIORITY_USER);

  return;
}

Up::Frame::~Frame(){};

Gtk::SizeRequestMode Up::Frame::get_request_mode_vfunc() const {
  return Gtk::Widget::get_request_mode_vfunc();
}

void Up::Frame::measure_vfunc(Gtk::Orientation _orientation,
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

void Up::Frame::on_map() {
  Gtk::Widget::on_map();
  return;
}

void Up::Frame::on_unmap() {
  Gtk::Widget::on_unmap();
  return;
}
void Up::Frame::on_realize() {
  Gtk::Widget::on_realize();
  return;
};
void Up::Frame::on_unrealize() {
  Gtk::Widget::on_unrealize();
  return;
};

void Up::Frame::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &snapshot) {
  const Gdk::Rectangle allocation = get_allocation();
  const Gdk::Rectangle rect(0, 0, allocation.get_width(),
                            allocation.get_height());

  auto cr = snapshot->append_cairo(rect);

  Gdk::Cairo::set_source_rgba(cr, bg_);
  cr->fill();

  return;
};
