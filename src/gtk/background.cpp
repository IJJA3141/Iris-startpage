#include "background.hpp"

Up::Background::Background(bool _fullscreen, int _width, int _height)
    : fullscreen_(_fullscreen) {

  set_title("Tmp");
  set_default_size(_width, _height);

  if (this->fullscreen_) {
    this->fullscreen();
    this->fullscreen_ = this->is_fullscreen();
  }

  set_child(this->frame_);

  return;
}
