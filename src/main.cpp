#include <iostream>

#include "gdkmm/pixbuf.h"
#include "glibmm/refptr.h"
#include "gtk/core/application.hpp"

int main(int _argc, char *_argv[])
{
  auto app = Iris::Application::create();
  //  Iris::ImageProcessor imp (5);
  //  imp.test ({ 5, 5, 10, 10 });
  return app->run(_argc, _argv);
}
