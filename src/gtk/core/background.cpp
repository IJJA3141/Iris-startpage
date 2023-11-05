#include "background.hpp"
#include "application.hpp"

Iris::Background::Background() : frame_() {
  set_title(APP_NAME);
  set_name("background");

  set_default_size(Iris::Application::config->get("width", 1000).asInt(),
                   Iris::Application::config->get("height", 500).asInt());

  if (Iris::Application::config->get("maximized", true).asBool())
    this->maximize();

  if (Iris::Application::config->get("fullscreen", false).asBool())
    this->is_fullscreen();

  set_child(this->frame_);

  return;
}
