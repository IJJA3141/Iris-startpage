#include "./ui/window.hpp"

#include <gtkmm.h>

int main(int _argc, char *_argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("");
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();

  css_provider->load_from_path("/home/alexe/Prog/Projects/Iris-startpage/tmp/style.css");

  Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), css_provider,
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  return app->make_window_and_run<Iris::Window>(_argc, _argv);
}
