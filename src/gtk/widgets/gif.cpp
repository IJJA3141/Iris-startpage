#include "gif.hpp"
#include "gdkmm/general.h"
#include "gdkmm/pixbuf.h"
#include <cairomm/context.h>
#include <cmath>
#include <ctime>
#include <glibmm/main.h>

Iris::Pane::Pane(std::string _, std::string __)
    : m_radius(0.42), m_line_width(0.05) {

  this->iter_ = Gdk::PixbufAnimation::create_from_file(
                    "/home/alexe/.config/iris/cbg-10.gif")
                    ->get_iter();

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Pane::on_timeout),
                                 1000);

  this->set_draw_func(sigc::mem_fun(*this, &Iris::Pane::on_draw));
  this->set_size_request(900, 900);

  return;
}

Iris::Pane::~Pane() {}

void Iris::Pane::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width,
                         int height) {
  this->iter_->advance();
  Gdk::Cairo::set_source_pixbuf(cr, this->iter_->get_pixbuf(), 100, 80);
  cr->rectangle(110, 90, this->iter_->get_pixbuf()->get_width() - 20,
                this->iter_->get_pixbuf()->get_height() - 20);

  cr->fill();

  return;
}

bool Iris::Pane::on_timeout() {
  // force our program to redraw the entire clock.
  this->queue_draw();

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Pane::on_timeout),
                                 this->iter_->get_delay_time());
  return false;
}
