#include "window.hpp"
#include "../EXAMPLE_CONFIG.hpp"

Iris::Window::Window() : stack_(), pg()
{
  this->set_title("Iris");

  this->stack_.set_name("stack");
  this->stack_.add(this->pg);

  this->stack_.set_visible_child(this->pg);
  this->set_child(this->stack_);

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
