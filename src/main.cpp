#include <iostream>

#include "gtk/core/application.hpp"

int main(int _argc, char *_argv[]) {
  auto app = Iris::Application::create();

  return app->run(_argc, _argv);
}
