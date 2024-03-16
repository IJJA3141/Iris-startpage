#ifndef _IRIS_WINDOW
#define _IRIS_WINDOW

#include "page.hpp"

#include <gtkmm.h>
#include <vector>

namespace Iris
{
class Window : public Gtk::Window
{
private:
  Iris::Page pg;
  Gtk::Stack stack_;

  // std::vector<Iris::Page *> vPPage_;

public:
  Window();

  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
};
} // namespace Iris

#endif // !_IRIS_WINDOW
