#include "app.hpp"
#include "const/file.hpp"
#include "lua/config.hpp"

#include <cstdlib>
#include <filesystem>
#include <gtk4-layer-shell.h>
#include <string>

Iris::Application::Application()
    : Gtk::Application("dev.ijja3141.iris", Gio::Application::Flags::NONE)
{
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  std::string configPath = getenv("XDG_CONFIG_HOME");

  if (std::filesystem::exists(configPath + "/iris/style.css"))
    css_provider->load_from_path(configPath + "/iris/style.css");
  else {
    configPath = std::getenv("HOME");
    if (std::filesystem::exists(configPath + "/iris/style.css"))
      css_provider->load_from_path(configPath + "/iris/style.css");
    else
      css_provider->load_from_path(APP_CONIF_PATH "/style.css");
  }

  Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), css_provider,
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  return;
};

Glib::RefPtr<Iris::Application> Iris::Application::create()
{
  return Glib::make_refptr_for_instance<Iris::Application>(new Iris::Application);
}

void Iris::Application::on_activate()
{
  this->pWindow_ = new Iris::Window();

  this->add_window(*this->pWindow_);

  if (Iris::ConfigRetriever::get_config_retriver()->config.isOverlay) {
    gtk_layer_init_for_window(this->pWindow_->gobj());
    gtk_layer_set_namespace(this->pWindow_->gobj(), "Iris");
    gtk_layer_set_margin(this->pWindow_->gobj(), GTK_LAYER_SHELL_EDGE_TOP, 0);
    gtk_layer_auto_exclusive_zone_enable(this->pWindow_->gobj());
    gtk_layer_set_layer(this->pWindow_->gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
    gtk_layer_set_keyboard_mode(this->pWindow_->gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_EXCLUSIVE);
  }

  this->pWindow_->present();
  this->pWindow_->maximize();

  return;
}
