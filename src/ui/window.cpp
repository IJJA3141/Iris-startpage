#include "window.hpp"

Iris::Window::Window() : index_(0), search_is_on_(false)
{
  for (Iris::Config::Page _ : Iris::ConfigRetriever::get_config_retriver()->config.vPage)
    this->vPPage_.push_back(new Iris::Page(_));

  for (int i = 0; i < this->vPPage_.size(); i++)
    this->stack_.add(*this->vPPage_[i]);

  this->set_title("Iris");

  this->set_margin(0);

  this->set_default_size(Iris::ConfigRetriever::get_config_retriver()->config.width,
                         Iris::ConfigRetriever::get_config_retriver()->config.height);

  this->set_name("background");

  this->stack_.set_visible_child(*this->vPPage_[0]);

  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Window::on_key_down),
                                               false);

  this->search_.set_visible(false);
  this->add_controller(pKeyController);

  this->overlay_.add_overlay(this->search_);

  this->overlay_.set_child(this->stack_);
  this->set_child(this->overlay_);

  return;
}

void Iris::Window::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation alloc;

  alloc.set_y((_height - Iris::ConfigRetriever::get_config_retriver()->config.height) / 2);
  alloc.set_height(Iris::ConfigRetriever::get_config_retriver()->config.height);

  alloc.set_x((_width - Iris::ConfigRetriever::get_config_retriver()->config.width) / 2);
  alloc.set_width(Iris::ConfigRetriever::get_config_retriver()->config.width);

  this->overlay_.size_allocate(alloc, _baseline);

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
