#ifndef BACKGROUND

#include <gtkmm.h>

#include "../../macros.hpp"
#include "../frame/frame.hpp"

#define BACKGROUND

namespace Up {

class Background : public Gtk::Window {
protected:
  bool fullscreen_;
  Up::Frame frame_;
  Gtk::Image img_;
  Gtk::Label label_;

public:
  Background(bool _fullscreen, int _width, int _height);
};

} // namespace Up

#endif // !BACKGROUND
