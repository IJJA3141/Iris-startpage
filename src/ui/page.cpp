#include "page.hpp"
#include "../lua/config.hpp"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>

Iris::Page::Page(int _index)
    : index_(_index),
      picture_(Iris::ConfigRetriever::get_config_retriver()->config.vPage[_index].image),
      box_(Gtk::Orientation::VERTICAL)
{
  int j;
  int i = 0;

  for (Iris::Config::Row __ :
       Iris::ConfigRetriever::get_config_retriver()->config.vPage[_index].aRow) {
    j = 0;

    Iris::Page::Row *pRow = new Iris::Page::Row();
    pRow->title = Gtk::Label(__.title);

    std::cout << __.title << " " << __.vButton.size() << std::endl;

    for (Iris::Config::Button _ : __.vButton) {
      Gtk::Button *pButton = new Gtk::Button(_.name);
      pButton->set_icon_name(_.image);

      pButton->signal_clicked().connect(sigc::mem_fun(_, &Iris::Config::Button::func));

      _.pageIndex = _index;
      _.row = i;
      _.buttonIndex = j;

      pRow->vPButton.push_back(pButton);
      pRow->box.append(*pButton);

      j++;
    }

    this->vPRow_.push_back(pRow);
    this->box_.append(pRow->box);
    i++;
  }

  // css class asignation
  this->box_.set_name("test_box");
  this->picture_.set_name("pic");
  this->set_name("page");

  // parenting
  this->picture_.set_parent(*this);
  this->box_.set_parent(*this);

  // settings
  this->picture_.set_size_request(1, 1);

  return;
}

void Iris::Page::measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum,
                               int &_natural, int &_minimum_baseline, int &_natural_baseline) const
{
  _minimum_baseline = -1;
  _natural = 0;
  _minimum = 0;

  return;
}

void Iris::Page::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation pic, buttons;

  pic.set_x(0);
  pic.set_width(Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  if (pic.get_width() < 300) pic.set_width(300);

  pic.set_y(0);
  pic.set_height(_height);
  if (pic.get_height()) pic.set_height(145);

  buttons.set_x(Iris::ConfigRetriever::get_config_retriver()->config.image_width);
  buttons.set_width(_width - Iris::ConfigRetriever::get_config_retriver()->config.image_width);

  buttons.set_y(0);
  buttons.set_height(_height);

  this->picture_.size_allocate(pic, _baseline);
  this->box_.size_allocate(buttons, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Page::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
