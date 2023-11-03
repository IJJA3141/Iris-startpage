#include "frame.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/text.h"

#include <gtkmm.h>

#ifndef BACKGROUND
#define BACKGROUND

namespace Up {

class Background : public Gtk::Window {
protected:
  bool fullscreen_;
  Up::Frame frame_;

public:
  Background(bool _fullscreen, int _width, int _height);
};

} // namespace Up

#endif // !BACKGROUND
