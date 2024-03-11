#include "search.hpp"
#include "../css.hpp"
#include "../xdg.hpp"
#include "gdk/gdkkeysyms.h"
#include "gdkmm/enums.h"
#include "gtkmm/eventcontrollerfocus.h"
#include "gtkmm/label.h"
#include "sigc++/functors/mem_fun.h"

#include <cctype>
#include <cstdlib>
#include <string>
#include <utility>

Iris::Search::Entry::Entry(Gtk::Box *_parent, std::pair<std::string, std::string> _pair)
    : name(_pair.first), command(_pair.second)
{
  this->pLable = new Gtk::Label(_pair.first);
  this->pLable->set_name(CSS_INACTIVE_LABEL);
  _parent->append(*this->pLable);

  return;
}

Iris::Search::Search()
    : vEntry_(), box_(Gtk::Orientation::VERTICAL), index_(0), scrolledWindow_(), labelCount_(0),
      bt("test")
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
  this->label_.set_name("entry_count");
  this->entry_.set_name("entry");

  // parenting
  this->entry_.set_parent(*this);
  this->label_.set_parent(*this);
  this->scrolledWindow_.set_parent(*this);
  this->scrolledWindow_.set_child(this->box_);

  // settings
  this->entry_.set_placeholder_text("App filter...");

  // events
  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Search::on_key_down),
                                               false);
  this->add_controller(pKeyController);

  this->entry_.signal_activate().connect(sigc::mem_fun(*this, &Iris::Search::handle_enter));
  this->entry_.property_text().signal_changed().connect(
      sigc::mem_fun(*this, &Iris::Search::handle_text));

  this->bt.set_parent(*this);

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

  Gtk::Allocation b;

  b.set_x(10);
  b.set_y(10);
  b.set_height(200);
  b.set_width(200);

  this->bt.size_allocate(b, _baseline);

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

  return false;
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

void Iris::Search::find(std::string _compared, std::string _comparing, Gtk::Label *_pLable)
{
  int size = _compared.size();
  std::string lowerCompared;
  bool out = false;
  int it = 0;

  if (_compared.size() < _comparing.size()) goto end;
  if (_comparing.size() == 0) {
    out = true;
    goto end;
  }

  for (const char c : _comparing)
    lowerCompared += std::tolower(c);

  _comparing = lowerCompared;
  lowerCompared.clear();

  for (const char c : _compared)
    lowerCompared += std::tolower(c);

  for (int i = 0; i < size - _comparing.size() + 1; i++) {
    if (lowerCompared.substr(i, _comparing.size()) == _comparing) {

      _compared.insert((6 + _comparing.size()) * it + i + _comparing.size(), "</b>");
      _compared.insert((6 + _comparing.size()) * it + i, "<b>");
      it++;

      out = true;
    };
  }

end:
  if (out) {
    _pLable->set_visible(true);
    _pLable->set_markup_with_mnemonic(_compared);
    this->labelCount_++;
  } else
    _pLable->set_visible(false);

  return;
}

void Iris::Search::handle_text()
{
  this->labelCount_ = 0;

  for (Iris::Search::Entry _ : this->vEntry_) {
    _.pLable->set_text(_.name);
    this->find(_.name, this->entry_.get_text(), _.pLable);
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

  if (this->labelCount_ < 10)
    this->label_.set_text(" " + std::to_string(this->labelCount_) + "/" +
                          std::to_string(this->vEntry_.size()));
  else
    this->label_.set_text(std::to_string(this->labelCount_) + "/" +
                          std::to_string(this->vEntry_.size()));

  return;
}

void Iris::Search::handle_enter()
{
  this->bt.grab_focus();

  std::string str = this->vEntry_[this->index_].command;
  if (str.find(" ") >= str.size()) return;
  system((str.erase(str.find(" ")) + " &").c_str());

  return;
};
