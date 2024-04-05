#include "window.hpp"
#include "gtkmm/enums.h"
#include "page.hpp"
#include <iostream>

Iris::Window::Window()
{
  this->set_title("Iris");

  this->set_name("background");

  for (int i = 0; i < Iris::ConfigRetriever::get_config_retriver()->config.vPage.size(); i++) {
    this->vPPage_.push_back(new Iris::Page(i));
  }

  this->stack_.set_name("stack");
  this->stack_.add(*this->vPPage_[0]);

  this->stack_.set_visible_child(*this->vPPage_[0]);
  this->set_child(this->stack_);

  // events

  return;
}

void Iris::Window::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation alloc;

  alloc.set_y((_height - Iris::ConfigRetriever::get_config_retriver()->config.height) / 2);
  alloc.set_height(Iris::ConfigRetriever::get_config_retriver()->config.height);

  alloc.set_x((_width - Iris::ConfigRetriever::get_config_retriver()->config.width) / 2);
  alloc.set_width(Iris::ConfigRetriever::get_config_retriver()->config.width);

  this->stack_.size_allocate(alloc, _baseline);

  std::cout << "Debug window size alloc\nNew height:"
            << ((_height - Iris::ConfigRetriever::get_config_retriver()->config.height) / 2)
            << "\nNew width"
            << ((_width - Iris::ConfigRetriever::get_config_retriver()->config.width) / 2)
            << std::endl;

  return;
};
