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
  auto app = Up::Application::create();

  return app->run(_argc, _argv);
}
