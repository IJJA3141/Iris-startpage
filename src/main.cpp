#include <iostream>

#include "gtk/core/application.hpp"
#include "image_processor.hpp"

int
main (int _argc, char *_argv[])
{
  // auto app = Iris::Application::create();
  Iris::ImageProcessor imp (5);

  return 0; // app->run(_argc, _argv);
}
