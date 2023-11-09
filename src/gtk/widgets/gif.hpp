#ifndef GIF

#include <gtkmm.h>
#include <iostream>
#include <string>

#define GIF

namespace Iris {
class Pane : public Gtk::DrawingArea {
private:
  Glib::RefPtr<Gdk::PixbufAnimationIter> iter_;
  std::string label_;

public:
  Pane(std::string _label, std::string _image_path);
  virtual ~Pane();

protected:
  bool on_timeout();
  void on_draw(const Cairo::RefPtr<Cairo::Context> &_cr, int _width,
               int _height);

  double m_radius;
  double m_line_width;
};
} // namespace Iris

#endif // !GIF
