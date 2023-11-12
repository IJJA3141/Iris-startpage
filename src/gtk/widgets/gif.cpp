#include "gif.hpp"

Iris::Pane::Pane (std::string _name, std::string _label, std::string _image_path) : label_ (_label)
{
  this->set_name (_name);

  this->iter_ = Gdk::PixbufAnimation::create_from_file (_image_path)->get_iter ();

  Glib::signal_timeout ().connect (sigc::mem_fun (*this, &Iris::Pane::on_timeout),
                                   this->iter_->get_delay_time ());

  this->set_draw_func (sigc::mem_fun (*this, &Iris::Pane::on_draw));
  this->set_size_request (this->iter_->get_pixbuf ()->get_width (),
                          this->iter_->get_pixbuf ()->get_height ());

  return;
}

Iris::Pane::~Pane () {}

void
Iris::Pane::on_draw (const Cairo::RefPtr<Cairo::Context> &_cr, int _width, int _height)
{
  Gdk::Cairo::set_source_pixbuf (_cr, this->iter_->get_pixbuf (), 100, 80);
  _cr->rectangle (110, 90, this->iter_->get_pixbuf ()->get_width () - 20,
                  this->iter_->get_pixbuf ()->get_height () - 20);

  //_cr->fill ();
  _cr->paint ();

  _cr->set_source_rgb (1.0, 1.0, 1.0);

  Pango::FontDescription font;

  font.set_family ("Monospace");
  font.set_weight (Pango::Weight::BOLD);

  auto layout = create_pango_layout ("Hi there!");

  layout->set_font_description (font);

  int text_width;
  int text_height;

  layout->get_pixel_size (text_width, text_height);

  //_cr->move_to((_width - text_width) / 2, (_height - text_height) / 2);

  layout->show_in_cairo_context (_cr);

  return;
}

bool
Iris::Pane::on_timeout ()
{
  this->queue_draw ();

  this->iter_->advance ();
  Glib::signal_timeout ().connect (sigc::mem_fun (*this, &Iris::Pane::on_timeout),
                                   this->iter_->get_delay_time ());
  return false;
}
