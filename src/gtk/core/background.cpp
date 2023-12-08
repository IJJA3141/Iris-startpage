#include "background.hpp"
#include "application.hpp"

Iris::Background::Background() : box_(Gtk::Orientation::VERTICAL), frame_("", nullptr), pages_(2)
{
  this->set_title(APP_NAME);
  this->set_name("background");

  this->set_default_size(Iris::Application::config->get("width", 1000).asInt(),
                         Iris::Application::config->get("height", 500).asInt());

  if (Iris::Application::config->get("maximized", true).asBool()) this->maximize();

  if (Iris::Application::config->get("fullscreen", false).asBool()) this->fullscreen();

  this->box_.append(this->frame_);
  this->box_.append(this->stack_);

  this->set_child(this->box_);

  return;
};

void Iris::Background::set_page(int _index)
{
  this->index_ = _index;
  this->frame_.swap(this->pages_[this->index_].iter);
  this->stack_.set_visible_child(this->pages_[this->index_].widget);

  return;
}

void Iris::Background::operator++()
{
  this->frame_.swap(this->pages_[++this->index_].iter);
  this->stack_.set_visible_child(this->pages_[this->index_].widget);

  return;
};

void Iris::Background::operator--()
{
  this->frame_.swap(this->pages_[--this->index_].iter);
  this->stack_.set_visible_child(this->pages_[this->index_].widget);

  return;
}
