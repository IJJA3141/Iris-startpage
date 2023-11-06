#include "module.hpp"
#include "../core/application.hpp"

Iris::Module::Module(std::string _name, std::string _label,
                     std::string _img_path, std::string _script_path)
    : hbox_(Gtk::Orientation::HORIZONTAL), script_(_script_path) {

  if (_img_path.at(0) == '~')
    _img_path = _img_path.replace(0, 1, Iris::Application::home);

  this->set_css_classes({"module"});
  this->set_name(_name + "-module");

  this->hbox_.set_css_classes({"module-box"});
  this->hbox_.set_name(_name + "-box");

  if (_img_path != "") {
    this->img_ = Gtk::Image(_img_path);

    this->img_.set_css_classes({"module-image"});
    this->img_.set_name(_name + "-image");

    this->hbox_.append(this->img_);
  }

  if (_label != "") {
    this->label_ = Gtk::Label(_label);

    this->label_.set_css_classes({"module-label"});
    this->label_.set_name(_name + "-label");

    this->hbox_.append(this->label_);
  }

  this->set_child(this->hbox_);

  this->signal_clicked().connect(sigc::mem_fun(*this, &Iris::Module::callback));

  this->debug_css();

  std::cout << "image path: " + _img_path << std::endl;

  return;
}

void Iris::Module::callback() {
  FILE *pipe = popen(("bash " + this->script_).c_str(), "r");

  if (pclose(pipe) != 0)
    std::cerr << "" << std::endl;
  return;
};

void Iris::Module::debug_css() {
  std::cout << "Module: " << this->get_name()
            << " Class: " << this->get_css_classes()[0]
            << "\nBox: " << this->hbox_.get_name()
            << " Class: " << this->hbox_.get_css_classes()[0]
            << "\nLabel: " << this->label_.get_name()
            << " Class: " << this->label_.get_css_classes()[0]
            << "\nImage: " << this->img_.get_name()
            << " Class: " << this->img_.get_css_classes()[0] << std::endl;

  std::cout << "bash script: " + this->script_ << std::endl;
}
