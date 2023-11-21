#include "frame.hpp"

Iris::Frame::Frame(std::string _name, Glib::RefPtr<Gdk::PixbufAnimationIter> _iter) : iter_(_iter)
{
  this->set_name(_name);

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Frame::on_timeout),
                                 this->iter_->get_delay_time());

  this->set_draw_func(sigc::mem_fun(*this, &Iris::Frame::on_draw));
  this->set_size_request(this->iter_->get_pixbuf()->get_width(),
                         this->iter_->get_pixbuf()->get_height());

  return;
}

bool Iris::Frame::on_timeout()
{
  this->queue_draw();

  this->iter_->advance();
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Frame::on_timeout),
                                 this->iter_->get_delay_time());

  return false;
}

void Iris::Frame::on_draw(const Cairo::RefPtr<Cairo::Context> &_cr, int _width, int _height)
{
  Gdk::Cairo::set_source_pixbuf(_cr, this->iter_->get_pixbuf(), 100, 80);
  _cr->rectangle(110, 90, this->iter_->get_pixbuf()->get_width() - 20,
                 this->iter_->get_pixbuf()->get_height() - 20);

  _cr->paint();

  return;
}
