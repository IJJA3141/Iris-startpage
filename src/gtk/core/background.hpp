#ifndef BG
#define BG

#include <gtkmm.h>
#include <vector>

#include "../../util/macros.hpp"
#include "../widgets/frame.hpp"

namespace Iris
{

struct Page {
  Glib::RefPtr<Gdk::PixbufAnimationIter> iter;
  Gtk::Widget widget;
};

class Background : public Gtk::Window
{
private:
  std::vector<Iris::Page> pages_;
  Iris::Frame frame_;
  Gtk::Stack stack_;
  Gtk::Box box_;
  int index_;

public:
  Background();
  void set_page(int _index);

public:
  void operator++();
  void operator--();
};

} // namespace Iris

#endif // !BG
