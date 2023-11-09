#include "gif.hpp"

Cairo::RefPtr<Cairo::Context> Iris::Pane::cr_ = nullptr;
Glib::RefPtr<Gdk::PixbufAnimationIter> Iris::Pane::buff_ = nullptr;

bool Iris::Pane::draw_image() {
  Iris::Pane::buff_->advance();
  /*
    Gdk::Cairo::set_source_pixbuf(Iris::Pane::cr_,
                                  Iris::Pane::buff_->get_pixbuf());

    Iris::Pane::cr_->rectangle(0, 0,
    Iris::Pane::buff_->get_pixbuf()->get_width(),
                               Iris::Pane::buff_->get_pixbuf()->get_height());
    Iris::Pane::cr_->fill();
    */
  std::cout << "??? " << Iris::Pane::buff_->get_delay_time() << std::endl;
  auto image = Gdk::Pixbuf::create_from_file(
      "/home/alexe/.config/iris/wallhaven-rrpp6m_2800x1800.png");
  Gdk::Cairo::set_source_pixbuf(Iris::Pane::cr_, image);
  Iris::Pane::cr_->rectangle(110, 90, image->get_width() - 20,
                             image->get_height() - 20);

  Iris::Pane::cr_->fill();

  return true;
}

Iris::Pane::Pane(std::string _label, std::string _image_path)
    : Gtk::Widget(), padding_(), label_(_label) {
  this->set_expand(true);

  this->set_name("test");

  this->buff_ = Gdk::PixbufAnimation::create_from_file(_image_path)->get_iter();

  return;
}

void Iris::Pane::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &_snapshot) {
  const auto allocation = get_allocation();
  const Gdk::Rectangle rect(0, 0, allocation.get_width(),
                            allocation.get_height());
  auto refStyleContext = get_style_context();

  // Create a cairo context to draw on.
  auto cr = _snapshot->append_cairo(rect);
  Iris::Pane::cr_ = _snapshot->append_cairo(rect);

  // paint the background
  // refStyleContext->render_background(
  //    cr, -this->padding_.get_left(), -this->padding_.get_top(),
  //    allocation.get_width(), allocation.get_height());

  // draw the foreground
  const double scale_x = 0.001 * (allocation.get_width());
  const double scale_y = 0.001 * (allocation.get_height());
  Gdk::Cairo::set_source_rgba(cr, refStyleContext->get_color());

  // Draw the image at 110, 90, except for the outermost 10 pixels.
  // cr->rectangle(110, 90, image->get_width() - 20, image->get_height() - 20);
  // cr->fill();

  Glib::signal_timeout().connect(sigc::ptr_fun(&Iris::Pane::draw_image), 100);
  return;
}

void Iris::Pane::measure_vfunc(Gtk::Orientation _orientation, int _for_size,
                               int &_minimum, int &_natural,
                               int &_minimum_baseline,
                               int &_natural_baseline) const {
  if (_orientation == Gtk::Orientation::HORIZONTAL) {
    _minimum = 60;
    _natural = 100;
  } else {
    _minimum = 50;
    _natural = 70;
  }

  // Don't use baseline alignment.
  _minimum_baseline = -1;
  _natural_baseline = -1;

  return;
}

void Iris::Pane::on_realize() {
  this->padding_ = this->get_style_context()->get_padding();

  Gtk::Widget::on_realize();

  return;
}
