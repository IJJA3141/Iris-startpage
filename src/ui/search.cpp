#include "search.hpp"
#include "../css.hpp"
#include "../xdg.hpp"
#include "gdk/gdkkeysyms.h"
#include "gdkmm/enums.h"
#include "gtkmm/eventcontrollerfocus.h"
#include "gtkmm/label.h"
#include "sigc++/functors/mem_fun.h"

#include <iostream>
#include <string>
#include <utility>

Iris::Search::Entry::Entry(Gtk::Box *_parent, std::pair<std::string, std::string> _pair)
{
  this->name = _pair.first;
  this->command = _pair.second;
  this->pLable = new Gtk::Label(_pair.first);
  this->pLable->set_name(CSS_INACTIVE_LABEL);
  _parent->append(*this->pLable);

  return;
}

Iris::Search::Search()
    : vEntry_(), box_(Gtk::Orientation::VERTICAL), index_(0), scrolledWindow_(), labelCount_(0)
{
  // initialization
  for (std::pair<std::string, std::string> _ : Iris::Xdg::fetch())
    this->vEntry_.push_back(Iris::Search::Entry(&this->box_, _));

  this->labelCount_ = this->vEntry_.size();
  this->adjustment_ = this->scrolledWindow_.get_vadjustment();

  this->label_.set_text(std::to_string(this->labelCount_) + "/" +
                        std::to_string(this->labelCount_));

  // css asignation
  this->box_.get_first_child()->set_name(CSS_ACTIVE_LABEL);
  this->label_.set_name("lab");
  this->entry_.set_name("ent");

  // parenting
  this->entry_.set_parent(*this);
  this->label_.set_parent(*this);
  this->scrolledWindow_.set_parent(*this);
  this->scrolledWindow_.set_child(this->box_);
  // settings
  this->set_focusable(false);
  this->label_.set_focusable(false);
  this->scrolledWindow_.set_focusable(false);
  this->entry_.set_placeholder_text("App filter...");

  // events
  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Search::on_key_down),
                                               false);
  const Glib::ustring a = "";
  this->add_controller(pKeyController);
  this->entry_.grab_focus();

  this->entry_.property_text().signal_changed().connect(
      sigc::mem_fun(*this, &Iris::Search::handle_text));

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

bool Iris::Search::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_ISO_Left_Tab ||
      _keyval == GDK_KEY_Tab &&
          (_state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK |
                     Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::SHIFT_MASK)
    this->handle_shift_tab();
  else if (_keyval == GDK_KEY_Tab)
    this->handle_tab();

  return true;
};

void Iris::Search::handle_tab()
{
  this->labelCount_ = 0;
  for (Iris::Search::Entry _ : this->vEntry_)
    if (_.pLable->get_visible()) this->labelCount_++;

  if (this->labelCount_ <= 1) return;

  this->vEntry_[this->index_++].pLable->set_name(CSS_INACTIVE_LABEL);
  if (this->index_ == this->vEntry_.size()) this->index_ = 0;

  while (!this->vEntry_[this->index_++].pLable->get_visible())
    if (this->index_ == this->vEntry_.size()) this->index_ = 0;

  this->vEntry_[--this->index_].pLable->set_name(CSS_ACTIVE_LABEL);

  this->adjustment_->set_value(this->adjustment_->get_page_size() * this->index_ /
                               this->labelCount_);

  return;
}

void Iris::Search::handle_shift_tab()
{
  this->labelCount_ = 0;
  for (Iris::Search::Entry _ : this->vEntry_)
    if (_.pLable->get_visible()) this->labelCount_++;

  if (this->labelCount_ <= 1) return;

  this->vEntry_[this->index_--].pLable->set_name(CSS_INACTIVE_LABEL);
  if (this->index_ == -1) this->index_ = this->vEntry_.size() - 1;

  while (!this->vEntry_[this->index_--].pLable->get_visible())
    if (this->index_ == -1) this->index_ = this->vEntry_.size() - 1;

  this->vEntry_[++this->index_].pLable->set_name(CSS_ACTIVE_LABEL);

  this->adjustment_->set_value(this->adjustment_->get_page_size() * this->index_ /
                               this->labelCount_);

  return;
}

void Iris::Search::handle_text()
{
  this->labelCount_ = 0;

  for (Iris::Search::Entry _ : this->vEntry_) {
    if (_.name.find(this->entry_.get_text()) == 0) {
      _.pLable->set_visible(true);
      this->labelCount_++;
    } else
      _.pLable->set_visible(false);
  }

  if (!this->vEntry_[this->index_].pLable->get_visible()) {

    if (this->labelCount_ == 0) return;
    this->vEntry_[this->index_].pLable->set_name(CSS_INACTIVE_LABEL);

    while (!this->vEntry_[this->index_--].pLable->get_visible())
      if (this->index_ == -1) this->index_ = this->vEntry_.size() - 1;

    this->vEntry_[++this->index_].pLable->set_name(CSS_ACTIVE_LABEL);
  }

  this->adjustment_->set_value(this->adjustment_->get_page_size() * this->index_ /
                               this->labelCount_);

  return;
}
