#ifndef GIF
#define GIF

#include <gtkmm.h>
#include <iostream>
#include <string>

#include "../../image_processor.hpp"

namespace Iris
{

class Pane : public Gtk::DrawingArea
{
private:
  Glib::RefPtr<Gdk::PixbufAnimationIter> iter_;
  std::string label_;

  Iris::ImageProcessor pr;

public:
  Pane(std::string _name, std::string _label, std::string _image_path);
  virtual ~Pane();

protected:
  bool on_timeout();
  void on_draw(const Cairo::RefPtr<Cairo::Context> &_cr, int _width, int _height);

  void blur(Cairo::Surface *_pCs, Cairo::Rectangle _rect, int _radius);
};
} // namespace Iris

#endif // !GIF
