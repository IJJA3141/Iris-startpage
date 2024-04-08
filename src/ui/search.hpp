#pragma once

#include <gtkmm.h>
#include <vector>

namespace Iris
{
class Search : public Gtk::Widget
{
private:
  struct Entry {
    const std::string name;
    const std::string command;
    Gtk::Label *pLabel;

    Entry(Gtk::Box *_parent, std::pair<std::string, std::string> _pair);
  };

private:
  Gtk::Entry entry_;
  Gtk::Label label_;
  Gtk::ScrolledWindow scrolledWindow_;
  Gtk::Box box_;
  std::vector<Iris::Search::Entry> vEntry_;
  int index_;
  int labelCount_;
  Glib::RefPtr<Gtk::Adjustment> adjustment_;

public:
  Search();

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};
} // namespace Iris
