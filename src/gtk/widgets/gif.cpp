#include "gif.hpp"
#include "gdkmm/pixbuf.h"
#include "glibmm/refptr.h"

#include "../../pixwrap.hpp"
#include <cstdlib>

Iris::Pane::Pane(std::string _name, std::string _label, std::string _image_path) : label_(_label)
{
  this->set_name(_name);

  this->iter_ = Gdk::PixbufAnimation::create_from_file(_image_path)->get_iter();

  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Pane::on_timeout),
                                 this->iter_->get_delay_time());

  this->set_draw_func(sigc::mem_fun(*this, &Iris::Pane::on_draw));
  this->set_size_request(this->iter_->get_pixbuf()->get_width(),
                         this->iter_->get_pixbuf()->get_height());

  return;
}

Iris::Pane::~Pane() {}

void access_pixel(Glib::RefPtr<Gdk::Pixbuf> imageptr, int x, int y)
{
  if (!imageptr) return;

  if (imageptr->get_colorspace() != Gdk::Colorspace::RGB) return;
  if (imageptr->get_bits_per_sample() != 8) return;
  if (!(x >= 0 && y >= 0 && x < imageptr->get_width() && y < imageptr->get_height())) return;

  int offset = y * imageptr->get_rowstride() + x * imageptr->get_n_channels();
  guchar *pixel = &imageptr->get_pixels()[offset]; // get pixel pointer
  std::cout << (int)pixel[0] << std::endl;   // conditionally modify the green channel

  pixel[0] = (guchar) 255;
  pixel[1] = (guchar) 0;
  pixel[2] = (guchar) 0;
}

void Iris::Pane::on_draw(const Cairo::RefPtr<Cairo::Context> &_cr, int _width, int _height)
{
  Gdk::Pixbuf::create_subpixbuf(this->iter_->get_pixbuf(), 0, 0, 100, 200);

  Gdk::Cairo::set_source_pixbuf(_cr, this->iter_->get_pixbuf(), 100, 80);
  _cr->rectangle(110, 90, this->iter_->get_pixbuf()->get_width() - 20,
                 this->iter_->get_pixbuf()->get_height() - 20);

  guint8 *a = this->iter_->get_pixbuf()->get_pixels();
  int b = this->iter_->get_pixbuf()->get_rowstride();
  std::cout << b << "!!!" << std::endl;
  /*
    Iris::Pixwrap k(this->iter_->get_pixbuf());
    k.debug();
  */

  access_pixel(this->iter_->get_pixbuf(), 1, 1);

  //_cr->fill ();
  _cr->paint();

  _cr->set_source_rgb(1.0, 1.0, 1.0);

  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::Weight::BOLD);

  auto layout = create_pango_layout("Hi there!");

  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  //_cr->move_to((_width - text_width) / 2, (_height - text_height) / 2);
  layout->show_in_cairo_context(_cr);

  std::shared_ptr<Cairo::Surface> test = _cr->get_target();

  switch (test->get_type()) {
  case Cairo::Surface::Type::IMAGE:
    std::cout << "IMG" << std::endl;
  case Cairo::Surface::Type::GL:
    std::cout << "GL" << std::endl;
  case Cairo::Surface::Type::PS:
    std::cout << "PS" << std::endl;
  case Cairo::Surface::Type::QT:
    std::cout << "QT" << std::endl;
  case Cairo::Surface::Type::VG:
    std::cout << "VG" << std::endl;
  case Cairo::Surface::Type::DRM:
    std::cout << "DRM" << std::endl;
  case Cairo::Surface::Type::OS2:
    std::cout << "OS2" << std::endl;
  case Cairo::Surface::Type::PDF:
    std::cout << "PDF" << std::endl;
  case Cairo::Surface::Type::TEE:
    std::cout << "TEE" << std::endl;
  case Cairo::Surface::Type::SVG:
    std::cout << "SVG" << std::endl;
  case Cairo::Surface::Type::XCB:
    std::cout << "XCB" << std::endl;
  case Cairo::Surface::Type::XML:
    std::cout << "XML" << std::endl;
  case Cairo::Surface::Type::BEOS:
    std::cout << "BEOS" << std::endl;
  case Cairo::Surface::Type::SKIA:
    std::cout << "SKIA" << std::endl;
  case Cairo::Surface::Type::XLIB:
    std::cout << "XLIB" << std::endl;
  case Cairo::Surface::Type::SUBSURFACE:
    std::cout << "SUBSURFACE" << std::endl;
  case Cairo::Surface::Type::GLITZ:
    std::cout << "GLITZ" << std::endl;
  case Cairo::Surface::Type::QUARTZ:
    std::cout << "QUARTZ" << std::endl;
  case Cairo::Surface::Type::WIN32:
    std::cout << "WIN32" << std::endl;
  case Cairo::Surface::Type::DIRECTFB:
    std::cout << "DIRECTFB" << std::endl;
  case Cairo::Surface::Type::WIN32_PRINTING:
    std::cout << "WIN32_PRINTING" << std::endl;
  case Cairo::Surface::Type::QUARTZ_IMAGE:
    std::cout << "QUARTZ_IMAGE" << std::endl;
  case Cairo::Surface::Type::RECORDING:
    std::cout << "RECORDING" << std::endl;
  case Cairo::Surface::Type::SCRIPT:
    std::cout << "SCRIPT" << std::endl;

  dedefault:
    std::cout << "Kill my self!!!" << std::endl;
  };
  return;
}

bool Iris::Pane::on_timeout()
{
  this->queue_draw();

  this->iter_->advance();
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Iris::Pane::on_timeout),
                                 this->iter_->get_delay_time());
  return false;
}
