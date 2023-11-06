#ifndef BACKGROUND

#include <gtkmm.h>
#include <iostream>
#include <json/json.h>
#include <vector>

#include "../../macros.hpp"
#include "../widgets/frame.hpp"
#include "../widgets/module.hpp"

#define BACKGROUND

namespace Iris {

class Background : public Gtk::Window {
private:
  Gtk::Box box_;
  Gtk::Grid rightBox_;
  Gtk::Image img_;

public:
  Background();

private:
  void debug_config();
};

} // namespace Iris

#endif // !BACKGROUND
