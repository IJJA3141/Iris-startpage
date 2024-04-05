#ifndef _IRIS_WINDOW
#define _IRIS_WINDOW

#include "gtkmm/label.h"
#include "gtkmm/picture.h"
#include "page.hpp"
#include "../lua/config.hpp"

#include <gtkmm.h>
#include <vector>

namespace Iris
{
class Window : public Gtk::Window
{
private:
  std::vector<Iris::Page *> vPPage_;
  Gtk::Stack stack_;
  Gtk::Picture test;

public:
  Window();

  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
};
} // namespace Iris

#endif // !_IRIS_WINDOW
