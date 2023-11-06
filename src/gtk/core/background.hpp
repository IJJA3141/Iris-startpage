#ifndef BACKGROUND

#include <gtkmm.h>

#include "../../macros.hpp"
#include "../widgets/frame.hpp"

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
};

} // namespace Iris

#endif // !BACKGROUND
