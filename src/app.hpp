#pragma once

#include "ui/window.hpp"

#include <gtkmm.h>

namespace Iris
{
class Application : public Gtk::Application
{
private:
  Iris::Window *pWindow_;

public:
  static Glib::RefPtr<Iris::Application> create();

protected:
  Application();
  void on_activate() override;
};
} // namespace Iris
