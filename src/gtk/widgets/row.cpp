#include "row.hpp"
#include "../core/application.hpp"
#include "module.hpp"

Iris::Row::Row (int _index, std::string _name, std::string _label)
    : Gtk::Box (Gtk::Orientation::VERTICAL), hbox_ (Gtk::Orientation::HORIZONTAL), label_ (_label)
{
  this->set_css_classes ({ "row" });
  this->set_name (_name + "-row");

  this->hbox_.set_css_classes ({ "row-modules" });
  this->hbox_.set_name (_name + "-row-modules");

  this->label_.set_css_classes ({ "row-label" });
  this->label_.set_name (_name + "-row-label");

  Json::Value modules = *Iris::Application::config;
  modules = modules["rows"][_index]["modules"];

  for (int i = 0; i < modules.size (); i++)
    this->hbox_.append (*Gtk::manage (new Iris::Module (
        modules[i].get ("name", "---").asString (), modules[i].get ("label", "---").asString (),
        modules[i].get ("icon", "---").asString (), modules[i].get ("script", "---").asString ())));

  this->append (this->label_);
  this->append (this->hbox_);

  // this->debug_css();

  return;
}

void
Iris::Row::debug_css ()
{
  std::cout << "Row: " << this->get_name () << " Class: " << this->get_css_classes ()[0]
            << "\nLable: " << this->label_.get_name ()
            << " Class: " << this->label_.get_css_classes ()[0]
            << "\nBox: " << this->hbox_.get_name ()
            << " Class: " << this->hbox_.get_css_classes ()[0] << std::endl;

  return;
}
