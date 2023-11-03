#include "application.hpp"
#include "background.hpp"
#include <giomm/application.h>
#include <glibmm/refptr.h>
#include <glibmm/ustring.h>
#include <gtk4-layer-shell.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <sigc++/adaptors/bind.h>
#include <sigc++/functors/mem_fun.h>

Up::Application::Application()
    : Gtk::Application("org.gtkmm.application",
                       Gio::Application::Flags::NONE) {}

Glib::RefPtr<Up::Application> Up::Application::create() {
  return Glib::make_refptr_for_instance<Up::Application>(new Up::Application);
}

Up::Background *Up::Application::create_appwindow() {
  Up::Background *win = new Up::Background(false, 600, 400);

  add_window(*win);

  gtk_layer_init_for_window(win->gobj());

  gtk_layer_set_layer(win->gobj(), GTK_LAYER_SHELL_LAYER_TOP);

  gtk_layer_auto_exclusive_zone_enable(win->gobj());

  gtk_window_present(win->gobj());

  win->signal_hide().connect(
      sigc::bind(sigc::mem_fun(*this, &Up::Application::on_hide_window), win));

  return win;
}

void Up::Application::on_activate() {
  Up::Background *win = create_appwindow();

  win->present();
}

void Up::Application::on_hide_window(Gtk::Window *_window) { delete _window; }
