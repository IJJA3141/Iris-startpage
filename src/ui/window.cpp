#include "window.hpp"

Iris::Window::Window() : lb("Hello World !")
{
  this->set_title("Iris");
  this->set_name("win");
  this->set_child(this->lb);
  return;
}
