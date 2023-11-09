#include "application.hpp"

std::string Iris::Application::home = Glib::getenv("HOME");
Json::Value *Iris::Application::config = nullptr;

Iris::Application::Application()
    : Gtk::Application("dev.ijja3141." APP_NAME, Gio::Application::Flags::NONE),
      css_provider_(nullptr) {
  std::fstream stream;
  Iris::Application::config = new Json::Value();

  stream.open(Iris::Application::home + "/.config/iris/config.json",
              std::ios::in);
  if (stream.is_open()) {
    stream >> *Iris::Application::config;
    stream.close();
  } else {
    stream.open("/etc/iris/config.json", std::ios::in);
    if (stream.is_open()) {
      stream >> *Iris::Application::config;
      stream.close();
    } else {
      std::cerr << ERR_LOAD_CONFIG << std::endl;
      exit(ERRNUM_LOAD_CONFIG);
    }
  }
  struct stat buffer;
  if (stat((Iris::Application::home + "/.config/iris/style.css").c_str(),
           &buffer) == 0) {
    this->css_provider_ = Gtk::CssProvider::create();
    this->css_provider_->load_from_path(Iris::Application::home +
                                        "/.config/iris/style.css");

    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), this->css_provider_,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  } else if (stat("etc/iris/style.css", &buffer) == 0) {
    this->css_provider_ = Gtk::CssProvider::create();
    this->css_provider_->load_from_path("/etc/iris/style.css");

    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), this->css_provider_,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  } else
    std::cerr << ERR_LOAD_CSS << std::endl;

  return;
};

Glib::RefPtr<Iris::Application> Iris::Application::create() {
  return Glib::make_refptr_for_instance<Iris::Application>(
      new Iris::Application);
}

Iris::Background *Iris::Application::create_appwindow() {
  Iris::Background *win = new Iris::Background();

  this->add_window(*win);

  if (Iris::Application::config->get("layer_top", true).asBool()) {
    gtk_layer_init_for_window(win->gobj());
    gtk_layer_set_namespace(win->gobj(), APP_NAME);
    gtk_layer_set_margin(
        win->gobj(), GTK_LAYER_SHELL_EDGE_TOP,
        Iris::Application::config->get("layer_margin_top", 0).asInt());
    gtk_layer_auto_exclusive_zone_enable(win->gobj());

    gtk_layer_set_layer(win->gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
  }

  win->signal_hide().connect(sigc::bind(
      sigc::mem_fun(*this, &Iris::Application::on_hide_window), win));

  return win;
}

void Iris::Application::on_activate() {
  Iris::Background *win = this->create_appwindow();

  win->present();
}

void Iris::Application::on_hide_window(Gtk::Window *_window) { delete _window; }
