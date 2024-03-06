#ifndef _IRIS_SEARCH
#define _IRIS_SEARCH

#include "../xdg.hpp"

#include <gtkmm.h>
#include <string>
#include <utility>
#include <vector>

namespace Iris
{

class Search : public Gtk::Widget
{
private:
  Gtk::Entry entry_;
  Gtk::Label label_;
  Gtk::ScrolledWindow scrolledWindow_;
  Gtk::Box box_;
  std::vector<Gtk::Label *> vPLabel_;

  int index_;
  std::vector<std::pair<std::string, std::string>> vPair_;

public:
  Search();

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;

private:
};
} // namespace Iris

#endif // !_IRIS_SEARCH
