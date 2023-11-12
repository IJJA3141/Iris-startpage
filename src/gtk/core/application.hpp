#ifndef APPLICATION

#include <fstream>
#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>
#include <json/json.h>
#include <string>

#include "../../macros.hpp"
#include "background.hpp"

#define APPLICATION

namespace Iris
{

class Application : public Gtk::Application
{
public:
  static Json::Value *config;
  static std::string home;

private:
  Glib::RefPtr<Gtk::CssProvider> css_provider_;

public:
  static Glib::RefPtr<Iris::Application> create ();

protected:
  Application ();
  void on_activate () override;

private:
  Iris::Background *create_appwindow ();
  void on_hide_window (Gtk::Window *_window);
};
} // namespace Iris

#endif // !APPLICATION
