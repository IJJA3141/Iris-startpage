#ifndef ROW

#include <gtkmm.h>
#include <string>

#define ROW

namespace Iris {

class Row : public Gtk::Box {
private:
  Gtk::Label label_;
  Gtk::Box hbox_;

public:
  Row(int _index, std::string _name, std::string _label);

private:
  void debug_css();
};
} // namespace Iris

#endif // ROW!
