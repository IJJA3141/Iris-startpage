#include "background.hpp"
#include "application.hpp"
#include <iostream>

Iris::Background::Background()
    : box_(Gtk::Orientation::HORIZONTAL), rightBox_(),
      img_("/home/alexe/.config/iris/wallhaven-rrpp6m_2800x1800.png") {
  this->set_title(APP_NAME);
  this->set_name("background");

  this->set_margin(0);

  this->set_default_size(Iris::Application::config->get("width", 1000).asInt(),
                         Iris::Application::config->get("height", 500).asInt());

  if (Iris::Application::config->get("maximized", true).asBool()) {
    std::cout << "max" << std::endl;
    this->maximize();
  }

  if (Iris::Application::config->get("fullscreen", false).asBool())
    this->fullscreen();

  this->rightBox_.set_margin(6);
  this->rightBox_.set_row_spacing(10);
  this->rightBox_.set_column_spacing(10);

  this->rightBox_.set_name("right");
  this->box_.set_name("box");
  this->img_.set_name("img");

  this->img_.set_expand(true);

  this->set_child(this->rightBox_);

  this->rightBox_.attach(this->img_, 0, 0);
  this->rightBox_.attach(this->box_, 0, 1);

  return;
}
