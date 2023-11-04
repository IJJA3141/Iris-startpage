#include "background.hpp"
#include "gdkmm/pixbuf.h"
#include "gdkmm/pixbufanimation.h"

Up::Background::Background(bool _fullscreen, int _width, int _height)
    : fullscreen_(_fullscreen), frame_() {

  set_title(APP_NAME);
  set_default_size(_width, _height);
  maximize();

  set_name("background");

  if (this->fullscreen_) {
    this->fullscreen();
    this->fullscreen_ = this->is_fullscreen();
  }

  set_child(this->frame_);

  // Gdk::PixbufAnimation::create_from_file(Glib::getenv("HOME") +
  //                                       "/.config/Up/cbg-10.gif");

  // set_child(this->img_);

  return;
}
