#include "frame.hpp"

Up::Frame::Frame()
    : img_(Glib::getenv("HOME") + ".config/Up/test.jpg"), label_("UwU"),
      left_() {
  this->set_name("frame");

  this->left_.set_childs(this->img_, this->label_);

  this->left_.set_parent(*this);
  // this->right_.set_parent(*this);

  return;
}

Up::Frame::~Frame(){};

/*
void Up::Frame::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &snapshot) {
  const Gdk::Rectangle allocation = get_allocation();
  const Gdk::Rectangle rect(0, 0, allocation.get_width(),
                            allocation.get_height());

  auto cr = snapshot->append_cairo(rect);

  Gdk::Cairo::set_source_rgba(cr, bg_);
  cr->fill();

  return;
};
*/
