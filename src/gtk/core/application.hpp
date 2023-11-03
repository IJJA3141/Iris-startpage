#ifndef APPLICATION

#include <gtkmm.h>

#include "../../macros.hpp"
#include "background.hpp"

#define APPLICATION

namespace Up {

class Application : public Gtk::Application {
protected:
  Application();

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
