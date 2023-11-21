#ifndef FRAME
#define FRAME

#include <cairo.h>
#include <gtkmm.h>
#include <string>
#include <vector>

namespace Iris
{

class Frame : public Gtk::DrawingArea
{
private:
  Glib::RefPtr<Gdk::PixbufAnimationIter> iter_;

public:
  Frame(std::string _name, Glib::RefPtr<Gdk::PixbufAnimationIter> _iter);
  void swap(Glib::RefPtr<Gdk::PixbufAnimationIter> _iter);

protected:
  bool on_timeout();
  void on_draw(const Cairo::RefPtr<Cairo::Context> &_cr, int _width, int _height);
};

} // namespace Iris

#endif // !FRAME
