#include "gtk/application.hpp"

#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>

int main(int _argc, char *_argv[]) {

  if (gtk_layer_is_supported()) {
    std::cout << "Ok!" << std::endl;
  } else {
    std::cout << "Gtk layer shell is not supported!" << std::endl;
    return 1;
  };

  // GtkApplication *app = gtk_application_new("test.id",
  // G_APPLICATION_DEFAULT_FLAGS); g_signal_connect(app, "activate",
  // G_CALLBACK(activate), NULL);

  auto app = Up::Application::create();

  return app->run(_argc, _argv);

  // int status = g_application_run(G_APPLICATION(app), _argc, _argv);
  // g_object_unref(app);
}
