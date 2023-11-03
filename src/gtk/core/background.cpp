#include "background.hpp"

Up::Background::Background(bool _fullscreen, int _width, int _height)
    : fullscreen_(_fullscreen) {

  set_title(APP_NAME);
  set_default_size(_width, _height);

  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("\
 * {background-color: transparent;}\
     ");

  this->get_style_context()->add_provider(css_provider,
                                          GTK_STYLE_PROVIDER_PRIORITY_USER);

  if (this->fullscreen_) {
    this->fullscreen();
    this->fullscreen_ = this->is_fullscreen();
  }

  set_child(this->frame_);

  return;
}
