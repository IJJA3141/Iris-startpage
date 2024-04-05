#ifndef _IRIS_PAGE
#define _IRIS_PAGE

#include "gtkmm/box.h"
#include "gtkmm/label.h"

#include <gtkmm.h>
#include <vector>

namespace Iris
{
class Page : public Gtk::Widget
{
private:
  struct Row {
    Gtk::Label title;
    Gtk::Box box;
    std::vector<Gtk::Button *> vPButton;
  };

private:
  int index_;
  Gtk::Picture picture_;
  std::vector<Iris::Page::Row *> vPRow_;
  Gtk::Box box_;

public:
  Page(int _index);

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};
} // namespace Iris

#endif // !_IRIS_PAGE
