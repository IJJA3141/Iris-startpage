#include "background.hpp"
#include "application.hpp"
#include "gtkmm/object.h"
#include <json/writer.h>

Iris::Background::Background()
    : box_(Gtk::Orientation::HORIZONTAL), rightBox_(),
      img_("/home/alexe/.config/iris/cbg-10.gif") {
  this->set_title(APP_NAME);
  this->set_name("background");

  this->set_default_size(Iris::Application::config->get("width", 1000).asInt(),
                         Iris::Application::config->get("height", 500).asInt());

  if (Iris::Application::config->get("maximized", true).asBool())
    this->maximize();

  if (Iris::Application::config->get("fullscreen", false).asBool())
    this->fullscreen();
  /*
    this->rightBox_.set_name("right");
    this->box_.set_name("box");
    this->img_.set_name("img");

    this->img_.set_expand(true);

    this->set_child(this->rightBox_);

    //this->rightBox_.attach(this->img_, 0, 0);
    this->rightBox_.attach(this->box_, 0, 1);

    this->box_.append(this->img_);
  */

  Json::Value modules = *Iris::Application::config;
  modules = modules["modules"];

  for (int i = 0; i < modules.size(); i++)
    this->box_.append(*Gtk::manage(
        new Iris::Module(modules[i].get("name", "---").asString(),
                         modules[i].get("label", "---").asString(),
                         modules[i].get("icon", "---").asString(),
                         modules[i].get("script", "---").asString())));

  this->set_child(this->box_);

  return;
}

void Iris::Background::debug_config() {

  Json::Value modules = *Iris::Application::config;
  modules = modules["modules"];

  for (int i = 0; i < modules.size(); i++) {
    std::cout << "Label: " << modules[i].get("label", "---").asString()
              << "\nIcon: " << modules[i].get("icon", "---").asString()
              << "\nScript: " << modules[i].get("script", "---").asString()
              << std::endl;
  }

  return;
}
