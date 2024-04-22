#include "app.hpp"

int main(int _argc, char *_argv[])
{
  Glib::RefPtr<Iris::Application> app = Iris::Application::create();

  return app->run(_argc, _argv);
}
