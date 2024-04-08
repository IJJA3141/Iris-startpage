#pragma once

#include "ui/window.hpp"

#include <gtkmm.h>

namespace Iris
{

class Application : public Gtk::Application
{
private:
  Iris::Window *window_;

public:
  static Glib::RefPtr<Iris::Application> create();

protected:
  Application();
  void on_activate() override;
};

} // namespace Iris
