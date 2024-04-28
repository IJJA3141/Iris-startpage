#include "window.hpp"
#include "../const/css.hpp"
#include "../lua/config.hpp"
#include "gtkmm/widget.h"
#include "search.hpp"

Iris::Window::Window() : search_()
{
  this->set_title("Iris");
  this->set_name(CSS_WINDOW);
  this->set_default_size(Iris::ConfigRetriever::get_config_retriver()->config.width,
                         Iris::ConfigRetriever::get_config_retriver()->config.height);

  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Window::on_key_down),
                                               false);
  this->add_controller(pKeyController);

  this->set_child(this->search_);

  return;
}

void Iris::Window::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation search;

  search.set_x(0);
  search.set_y(0);
  search.set_width(_width);
  search.set_height(_height);

  this->search_.size_allocate(search, _baseline);

  return;
};

bool Iris::Window::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_q || _keyval == GDK_KEY_Escape) exit(0);

  return false;
}
