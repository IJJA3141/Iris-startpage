#ifndef _IRIS_PAGE
#define _IRIS_PAGE

#include "gtkmm/scrolledwindow.h"
#include "search.hpp"
#include <gtkmm.h>

namespace Iris
{
class Page : public Gtk::Widget
{
private:
  Gtk::Picture picture_;
  Iris::Search search_;

public:
  Page();

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};
} // namespace Iris

#endif // !_IRIS_PAGE
