#ifndef MODULE

#include <algorithm>
#include <gtkmm.h>
#include <iostream>
#include <string>

#define MODULE

namespace Iris
{

class Module : public Gtk::Button
{
private:
  Gtk::Label label_;
  Gtk::Image img_;
  Gtk::Box hbox_;
  std::string script_;

public:
  Module (std::string _name, std::string _label, std::string _img_path, std::string _script_path);

protected:
  void callback ();
  void debug_css ();
};
}; // namespace Iris

#endif // !MODULE
