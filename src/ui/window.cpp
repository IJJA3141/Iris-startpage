#include "window.hpp"
#include <iostream>

#define b                                                                                          \
  {                                                                                                \
    0, 0, i++, "label", "/etc/iris/logo.png"                                                       \
  }

Iris::Window::Window() : search_("-----------------------------"), index_(0), search_is_on_(false)
{
  int i = 0;

  Iris::Config::Row row0{"title 0", {b, b, b, b}};
  Iris::Config::Row row1{"title 1", {b, b, b, b}};
  Iris::Config::Row row2{"title 2", {b, b, b, b}};

  Iris::Config::Page ppage = {"name", "/home/alexe/.config/iris/test.png", {row0, row1, row2}};

  this->vPPage_.push_back(new Iris::Page(ppage));
  ppage = {"name", "/home/alexe/.config/iris/test.jpg", {row0, row1, row2}};
  this->vPPage_.push_back(new Iris::Page(ppage));
  ppage = {"name", "/home/alexe/.config/iris/test.gif", {row0, row1, row2}};
  this->vPPage_.push_back(new Iris::Page(ppage));
  this->vPPage_.push_back(new Iris::Page(ppage));

  for (int i = 0; i < this->vPPage_.size(); i++)
    this->stack_.add(*this->vPPage_[i]);

  this->set_title("Iris");

  this->set_name("background");

  this->stack_.set_visible_child(*this->vPPage_[0]);

  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Window::on_key_down),
                                               false);

  this->add_controller(pKeyController);

  this->set_child(this->stack_);
  this->set_child(this->search_);

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

  alloc.set_width(((_width - Iris::ConfigRetriever::get_config_retriver()->config.width) / 2) -
                  Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  alloc.set_x(((_width - Iris::ConfigRetriever::get_config_retriver()->config.width) / 2) +
              Iris::ConfigRetriever::get_config_retriver()->config.image_width);

  this->search_.size_allocate(alloc, _baseline);

  return;
};

void Iris::Window::swap_search()
{
  this->search_is_on_ = !this->search_is_on_;
  this->search_.set_visible(this->search_is_on_);

  return;
}

void Iris::Window::operator++()
{
  if (++this->index_ == this->vPPage_.size()) this->index_ = 0;

  this->stack_.set_visible_child(*this->vPPage_[this->index_]);

  return;
}
void Iris::Window::operator--()
{
  if (--this->index_ == -1) this->index_ = this->vPPage_.size() - 1;

  this->stack_.set_visible_child(*this->vPPage_[this->index_]);

  return;
}

bool Iris::Window::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_q)
    this->operator--();
  else if (_keyval == GDK_KEY_e)
    this->operator++();
  else if (_keyval == GDK_KEY_i)
    this->swap_search();

  return false;
}
