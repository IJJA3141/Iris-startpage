#include "search.hpp"
#include "../css.hpp"
#include "../lua/config.hpp"

Iris::Search::Entry::Entry(Gtk::Box *_parent, std::pair<std::string, std::string> _pair)
    : name(_pair.first), command(_pair.second)
{
  this->pLabel = new Gtk::Label(_pair.first);
  this->pLabel->set_name(CSS_INACTIVE_LABEL);
  _parent->append(*this->pLabel);

  return;
}

Iris::Search::Search() : box_(Gtk::Orientation::VERTICAL), index_(0), labelCount_(0)
{
  for (std::pair<std::string, std::string> _ : Iris::xdg::fetch())
    this->vEntry_.push_back(Iris::Search::Entry(&this->box_, _));

  this->labelCount_ = this->vEntry_.size();
  this->adjustment_ = this->scrolledWindow_.get_vadjustment();

  this->label_.set_text(std::to_string(this->labelCount_) + "/" +
                        std::to_string(this->labelCount_));

  this->entry_.set_parent(*this);
  this->label_.set_parent(*this);
  this->scrolledWindow_.set_parent(*this);
  this->scrolledWindow_.set_child(this->box_);

  this->entry_.set_placeholder_text("App filter...");

  return;
};

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

  Gtk::Allocation b;

  b.set_x(10);
  b.set_y(10);
  b.set_height(200);
  b.set_width(200);

  this->box_.size_allocate(b, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Search::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
