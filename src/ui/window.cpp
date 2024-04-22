#include "window.hpp"
#include "../const/css.hpp"
#include "../lua/config.hpp"

Iris::Window::Window()
{
  this->set_title("Iris");
  this->set_name(CSS_WINDOW);
  this->set_default_size(Iris::ConfigRetriever::get_config_retriver()->config.width,
                         Iris::ConfigRetriever::get_config_retriver()->config.height);

  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Window::on_key_down),
                                               false);
  this->add_controller(pKeyController);

  return;
}

void Iris::Window::size_allocate_vfunc(int _width, int _height, int _baseline) { return; };

bool Iris::Window::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_q || _keyval == GDK_KEY_Escape) exit(0);

  return false;
}
