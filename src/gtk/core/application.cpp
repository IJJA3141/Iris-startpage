#include "application.hpp"
#include "gdkmm/display.h"
#include "gtkmm/stylecontext.h"

Up::Application::Application()
    : Gtk::Application("dev.ijja3141." APP_NAME,
                       Gio::Application::Flags::NONE) {

  if (!gtk_layer_is_supported()) {
    std::cout << "Gtk layer shell is not supported!" << std::endl;
  }

  this->home_ = Glib::getenv("HOME");
  this->css_provider_ = Gtk::CssProvider::create();
  this->css_provider_->load_from_path(this->home_ + "/.config/Up/style.css");

  Gtk::StyleContext::add_provider_for_display(
      Gdk::Display::get_default(), this->css_provider_,
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

Glib::RefPtr<Up::Application> Up::Application::create() {
  return Glib::make_refptr_for_instance<Up::Application>(new Up::Application);
}

Up::Background *Up::Application::create_appwindow() {
  Up::Background *win = new Up::Background(true, 2880, 1800);

  /*
  auto test = Gdk::Display::get_default()->get_monitors();
  test;
  */

  add_window(*win);

  gtk_layer_init_for_window(win->gobj());
  gtk_layer_set_namespace(win->gobj(), APP_NAME);
  gtk_layer_set_layer(win->gobj(), GTK_LAYER_SHELL_LAYER_TOP);
  gtk_layer_auto_exclusive_zone_enable(win->gobj());

  win->signal_hide().connect(
      sigc::bind(sigc::mem_fun(*this, &Up::Application::on_hide_window), win));

  return win;
}

void Up::Application::on_activate() {
  Up::Background *win = create_appwindow();

  win->present();
}

void Up::Application::on_hide_window(Gtk::Window *_window) { delete _window; }
