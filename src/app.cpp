#include "app.hpp"
#include "gtk4-layer-shell.h"

#include <filesystem>

Iris::Application::Application()
    : Gtk::Application("dev.ijja3141.iris", Gio::Application::Flags::NONE)
{
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();

  std::string str = std::getenv("XDG_CONFIG_HOME");

  if (std::filesystem::exists(str + "/iris/style.css"))
    css_provider->load_from_path(str + "/iris/style.css");
  else {
    str = std::getenv("HOME");

    if (std::filesystem::exists(str + "/.config/iris/style.css"))
      css_provider->load_from_path(str + "/.config/iris/style.css");
    else
      css_provider->load_from_path("/etc/iris/style.css");
  }

  Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), css_provider,
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  return;
}

Glib::RefPtr<Iris::Application> Iris::Application::create()
{
  return Glib::make_refptr_for_instance<Iris::Application>(new Iris::Application);
}

void Iris::Application::on_activate()
{
  this->window_ = new Iris::Window();

  this->add_window(*this->window_);

  if (Iris::ConfigRetriever::get_config_retriver()->config.is_overlay) {
    gtk_layer_init_for_window(this->window_->gobj());
    gtk_layer_set_namespace(this->window_->gobj(), "Iris");
    gtk_layer_set_margin(this->window_->gobj(), GTK_LAYER_SHELL_EDGE_TOP, 0);
    gtk_layer_auto_exclusive_zone_enable(this->window_->gobj());
    gtk_layer_set_layer(this->window_->gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
    gtk_layer_set_keyboard_mode(this->window_->gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_EXCLUSIVE);
  }

  this->window_->present();

  this->window_->maximize();

  return;
};
