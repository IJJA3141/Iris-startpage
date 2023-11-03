#include "glibmm/miscutils.h"
#include "glibmm/refptr.h"
#include "gtk/core/application.hpp"
#include "gtkmm/cssprovider.h"
#include "gtkmm/stylecontext.h"

#include <cstddef>
#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>
#include <string>
#include <unistd.h>

int main(int _argc, char *_argv[]) {

  if (!gtk_layer_is_supported()) {
    std::cout << "Gtk layer shell is not supported!" << std::endl;
    return 1;
  }

  Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();

  std::string homedir;
  if ((homedir = Glib::getenv("HOME")) == "") {
  }

  provider->load_from_path(homedir + "/.config/Up/style.css");

  auto app = Up::Application::create();

  return app->run(_argc, _argv);
}
