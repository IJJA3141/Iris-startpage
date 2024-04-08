#include "app.hpp"

int main(int _argc, char *_argv[])
{
  auto app = Iris::Application::create();

  int r = app->run(_argc, _argv);

  return r;
}
