#ifndef _IRIS_SEARCH
#define _IRIS_SEARCH

#include "glibmm/ustring.h"
#include "gtkmm/adjustment.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/label.h"

#include <gtkmm.h>
#include <string>
#include <utility>
#include <vector>

namespace Iris
{

class Search : public Gtk::Widget
{
private:
  struct Entry {
    std::string name;
    std::string command;
    Gtk::Label *pLable;

    Entry(Gtk::Box *_parent, std::pair<std::string, std::string> _pair);
  };

private:
  Gtk::Entry entry_;
  Gtk::Label label_;
  Gtk::ScrolledWindow scrolledWindow_;
  Gtk::Box box_;
  std::vector<Iris::Search::Entry> vEntry_;
  int index_;

  Glib::RefPtr<Gtk::Adjustment> adjustment_;
  int labelCount_;

public:
  Search();

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;

private:
  bool on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state);
  void handle_tab();
  void handle_shift_tab();
  void handle_text();

private:
};
} // namespace Iris

#endif // !_IRIS_SEARCH
