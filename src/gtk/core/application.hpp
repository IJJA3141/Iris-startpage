#ifndef APPLICATION

#include <gtk4-layer-shell.h>
#include <gtkmm.h>
#include <iostream>
#include <string>

#include "../../macros.hpp"
#include "background.hpp"

#define APPLICATION

namespace Up {

class Application : public Gtk::Application {
protected:
  Application();
  Glib::RefPtr<Gtk::CssProvider> css_provider_;
  std::string home_;

public:
  static Glib::RefPtr<Application> create();

protected:
  void on_activate() override;

private:
  Up::Background *create_appwindow();
  void on_hide_window(Gtk::Window *_window);
};

} // namespace Up

#endif // !APPLICATION
