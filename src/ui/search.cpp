#include "search.hpp"

#include <string>
#include <utility>

Iris::Search::Search()
    : vPair_(Iris::Xdg::fetch()), box_(Gtk::Orientation::VERTICAL), index_(0), scrolledWindow_()
{
  // initialization
  this->label_.set_text(std::to_string(this->vPair_.size()) + "/" +
                        std::to_string(this->vPair_.size()));

  this->entry_.set_placeholder_text("App filter...");

  for (const std::pair<std::string, std::string> entry : this->vPair_) {
    this->vPLabel_.push_back(new Gtk::Label(entry.first));
    this->box_.append(*(this->vPLabel_[this->vPLabel_.size() - 1]));
    this->box_.get_last_child()->set_name("one");
  }

  // css asignation
  this->box_.get_first_child()->set_name("two");
  this->label_.set_name("lab");
  this->entry_.set_name("ent");

  // parenting
  this->entry_.set_parent(*this);
  this->label_.set_parent(*this);
  this->scrolledWindow_.set_parent(*this);

  this->scrolledWindow_.set_child(this->box_);

  // settings
  this->scrolledWindow_.set_focusable(false);

  return;
}

void Iris::Search::measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum,
                                 int &_natural, int &_minimum_baseline,
                                 int &_natural_baseline) const
{
  _minimum_baseline = -1;
  _natural = 0;
  _minimum = 0;

  return;
}

void Iris::Search::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  // minEntry = min height; minLabel = min width
  Gtk::Allocation entry, label, scrolled;
  int minEntry, minLabel, nat, minBaseline, natBaseline;

  this->entry_.measure(Gtk::Orientation::HORIZONTAL, _width, minEntry, nat, minBaseline,
                       natBaseline);
  this->label_.measure(Gtk::Orientation::HORIZONTAL, minEntry, minLabel, nat, minBaseline,
                       natBaseline);

  entry.set_x(0);
  entry.set_y(0);
  entry.set_width(_width - minLabel);
  entry.set_height(minEntry);

  label.set_x(_width - minLabel);
  label.set_y(0);
  label.set_width(minLabel);
  label.set_height(minEntry);

  scrolled.set_x(0);
  scrolled.set_y(minEntry);
  scrolled.set_width(_width);
  scrolled.set_height(_height - minEntry);

  this->entry_.size_allocate(entry, _baseline);
  this->label_.size_allocate(label, _baseline);
  this->scrolledWindow_.size_allocate(scrolled, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Search::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
