#include "window.hpp"
#include "../EXAMPLE_CONFIG.hpp"
#include "gtkmm/enums.h"

Iris::Window::Window() : stack_(), pg(), pg2()
{
  this->set_title("Iris");

  this->set_name("background");

  this->stack_.set_name("stack");
  this->stack_.add(this->pg);
  this->stack_.add(this->pg2);

  this->stack_.set_visible_child(this->pg);
  this->set_child(this->stack_);

  // events
  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Window::on_key_down),
                                               false);
  this->add_controller(pKeyController);

  this->stack_.set_transition_type(Gtk::StackTransitionType::OVER_UP);

  return;
}

void Iris::Window::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation aloc;

  aloc.set_y((_height - _IRIS_EXAMPLE_CONFIG_HEIGHT) / 2);
  aloc.set_height(_IRIS_EXAMPLE_CONFIG_HEIGHT);

  aloc.set_x((_width - _IRIS_EXAMPLE_CONFIG_WIDTH) / 2);
  aloc.set_width(_IRIS_EXAMPLE_CONFIG_WIDTH);

  this->stack_.size_allocate(aloc, _baseline);

  return;
};

bool Iris::Window::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_h) this->stack_.set_visible_child(this->pg2);

  return true;
};
