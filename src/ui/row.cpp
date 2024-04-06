#include "./row.hpp"
#include <iostream>

Iris::Row::Row() { return; };

Iris::Row::Row(Iris::Config::Row const &_row)
    : title_(_row.title, Gtk::Align::START), box_(Gtk::Orientation::HORIZONTAL)
{
  for (int i = 0; i < _row.vButton.size(); i++) {
    Gtk::Button *pButton;
    if (_row.vButton[i].image == "") {
      pButton = new Gtk::Button(_row.vButton[i].label);
    } else {
      pButton = new Gtk::Button();
      Gtk::Box *pBox = new Gtk::Box(Gtk::Orientation::HORIZONTAL);
      pBox->append(*(new Gtk::Picture(_row.vButton[i].image)));
      pBox->append(*(new Gtk::Label(_row.vButton[i].label)));
      pButton->set_child(*pBox);
    }

    pButton->signal_clicked().connect([=] {
      Iris::ConfigRetriever::get_config_retriver()->call_function(
          _row.vButton[i].page_id, _row.vButton[i].row_id, _row.vButton[i].button_id);
      return;
    });

    this->box_.append(*pButton);
    this->vPButton_.push_back(pButton);
  }

  this->title_.set_parent(*this);
  this->box_.set_parent(*this);

  this->set_expand(true);

  return;
}

void Iris::Row::measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum,
                              int &_natural, int &_minimum_baseline, int &_natural_baseline) const
{
  int minLabel, natLabel, minBaselineLabel, natBaselineLabel;
  int minBox, natBox, minBaselineBox, natBaselineBox;

  _minimum_baseline = -1;

  if (_orientation == Gtk::Orientation::HORIZONTAL) {
    this->title_.measure(Gtk::Orientation::HORIZONTAL, _for_size, minLabel, natLabel,
                         minBaselineLabel, natBaselineLabel);

    this->title_.measure(Gtk::Orientation::HORIZONTAL, _for_size, minBox, natBox, minBaselineBox,
                         natBaselineBox);
  } else {
    this->title_.measure(Gtk::Orientation::VERTICAL, _for_size, minLabel, natLabel,
                         minBaselineLabel, natBaselineLabel);

    this->title_.measure(Gtk::Orientation::VERTICAL, _for_size, minBox, natBox, minBaselineBox,
                         natBaselineBox);
  }

  _minimum = minLabel + minBox;
  _natural = natLabel + natBox;

  return;
}

void Iris::Row::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation title, box;
  int min, nat, minBaseline, natBaseline;

  this->title_.measure(Gtk::Orientation::HORIZONTAL, _width, min, nat, minBaseline, natBaseline);

  title.set_width(_width);
  title.set_height(min);
  title.set_x(0);
  title.set_y(0);

  box.set_width(_width);
  box.set_height(_height - min);
  box.set_x(0);
  box.set_y(min);

  std::cout << "height: " << _height << "\nwidth: "
            << _width - Iris::ConfigRetriever::get_config_retriver()->config.image_width
            << std::endl;

  this->title_.size_allocate(title, _baseline);
  this->box_.size_allocate(box, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Row::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::WIDTH_FOR_HEIGHT;
}
