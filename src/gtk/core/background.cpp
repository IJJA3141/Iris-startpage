#include "background.hpp"
#include "application.hpp"

Iris::Background::Background()
    : box_(Gtk::Orientation::VERTICAL), rightBox_(),
      img_("/home/alexe/.config/iris/cbg-10.gif"), gif_("label", "/home/alexe/.config/iris/cbg-10.gif") {
  this->set_title(APP_NAME);
  this->set_name("background");

  this->set_default_size(Iris::Application::config->get("width", 1000).asInt(),
                         Iris::Application::config->get("height", 500).asInt());

  if (Iris::Application::config->get("maximized", true).asBool())
    this->maximize();

  if (Iris::Application::config->get("fullscreen", false).asBool())
    this->fullscreen();

  Json::Value rows = *Iris::Application::config;
  rows = rows["rows"];

  for (int i = 1000; i < rows.size(); i++)
    this->box_.append(
        *Gtk::manage(new Iris::Row(i, rows[i].get("name", "---").asString(),
                                   rows[i].get("label", "---").asString())));

  this->box_.append(this->gif_);

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
