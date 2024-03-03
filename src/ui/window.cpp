#include "window.hpp"

Iris::Window::Window() : stack_(), pg()
{
  this->set_title("Iris");

  this->stack_.set_size_request(200, 200);
  this->stack_.set_name("stack");
  this->stack_.add(this->pg);

  // for (Iris::Page *pPage : this->vPPage_)
  //   this->stack_.add(*pPage);

  this->stack_.set_visible_child(this->pg);
  this->set_child(this->stack_);

  return;
}
