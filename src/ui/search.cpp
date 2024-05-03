#include "search.hpp"
#include "../const/css.hpp"
#include "../const/error.hpp"
#include "../const/label.hpp"
#include "../lua/config.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

Iris::Search::Search()
    : index_(0), searchBox_(Gtk::Orientation::HORIZONTAL), leftLabel_(SEARCH_LEFT_LABEL),
      vEntry_(Iris::xdg::fetch()),
      entryNumber_(Iris::ConfigRetriever::get_config_retriver()->config.entryNumber),
      entryBox_(Gtk::Orientation::VERTICAL)
{
  this->rightLabel_.set_text("0/" + std::to_string(this->vEntry_.size()));

  this->searchBox_.append(this->entry_);
  this->searchBox_.append(this->leftLabel_);
  this->searchBox_.append(this->rightLabel_);
  this->entry_.set_expand(true);

  for (int i = 0; i < this->entryNumber_; i++) {
    this->vPLabel_.push_back(new Gtk::Label);
    this->entryBox_.append(*this->vPLabel_[i]);
    this->vPLabel_[i]->set_expand(true);
    this->vPLabel_[i]->set_name(CSS_INACTIVE_LABEL);
  }

  this->vPLabel_[0]->set_name(CSS_ACTIVE_LABEL);

  this->searchBox_.set_parent(*this);
  this->entryBox_.set_parent(*this);

  Glib::RefPtr<Gtk::EventControllerKey> pKeyController = Gtk::EventControllerKey::create();
  pKeyController->signal_key_pressed().connect(sigc::mem_fun(*this, &Iris::Search::on_key_down),
                                               false);
  this->entry_.add_controller(pKeyController);

  this->entry_.signal_activate().connect(sigc::mem_fun(*this, &Iris::Search::run));
  this->entry_.property_text().signal_changed().connect(sigc::mem_fun(*this, &Iris::Search::match));

  this->match();
  this->show_entrys();

  return;
}

void Iris::Search::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation searchBox;
  Gtk::Allocation entryBox;

  int minimum, natural, minimumBaseline, naturalBaseline;

  this->searchBox_.measure(Gtk::Orientation::HORIZONTAL, _width, minimum, natural, minimumBaseline,
                           naturalBaseline);

  searchBox.set_x(0);
  searchBox.set_y(0);
  searchBox.set_width(_width);
  searchBox.set_height(minimum);

  entryBox.set_x(0);
  entryBox.set_y(minimum);
  entryBox.set_width(_width);
  entryBox.set_height(_height - minimum);

  this->searchBox_.size_allocate(searchBox, _baseline);
  this->entryBox_.size_allocate(entryBox, _baseline);

  return;
}

bool Iris::Search::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_Escape) {
    this->get_parent()->grab_focus();
    return false;
  }

  if (_keyval == GDK_KEY_Tab || _keyval == GDK_KEY_ISO_Left_Tab) {
    this->vPLabel_[this->index_ % this->entryNumber_]->set_name(CSS_INACTIVE_LABEL);

    if (_state == Gdk::ModifierType::SHIFT_MASK) {
      if (--this->index_ >= this->pMatchingEntry_.size())
        this->index_ = this->pMatchingEntry_.size() - 1;
    } else if (++this->index_ >= this->pMatchingEntry_.size())
      this->index_ = 0;

    this->vPLabel_[this->index_ % this->entryNumber_]->set_name(CSS_ACTIVE_LABEL);

    this->show_entrys();

    return true;
  }

  return false;
}

void Iris::Search::grab_focus()
{
  this->entry_.grab_focus();
  return;
}

void Iris::Search::show_entrys()
{
  int indexFirst = this->index_ / this->entryNumber_;

  for (Gtk::Label *_ : this->vPLabel_) {
    _->set_text("");
  }

  for (int i = 0; i < this->entryNumber_; i++) {
    if (i + indexFirst * this->entryNumber_ >= this->pMatchingEntry_.size()) break;

    this->vPLabel_[i]->set_markup_with_mnemonic(
        this->pMatchingEntry_[i + indexFirst * this->entryNumber_].second.label);
  }

  return;
}

std::string to_lower(std::string _str)
{
  std::string str;

  for (int i = 0; i < _str.size(); i++) {
    if (65 <= (int)_str[i] && (int)_str[i] <= 90)
      str += _str[i] + 32;
    else
      str += _str[i];
  }

  return str;
}

int common(std::string &_compared, std::string _comparing)
{
  int it = 0;

  std::string lower_conapred = to_lower(_compared);
  _comparing = to_lower(_comparing);

  for (int i = 0; i < lower_conapred.size() - 1; i++) {
    if (lower_conapred.substr(i, _comparing.size()) == _comparing) {
      _compared.insert((6 + _comparing.size()) * it + i + _comparing.size(), "</b>");
      _compared.insert((6 + _comparing.size()) * it++ + i, "<b>");
    }
  }

  return it;
}

bool sort(std::pair<int, Iris::Entry> &_a, std::pair<int, Iris::Entry> &_b)
{
  return _a.first > _b.first;
}

void Iris::Search::match()
{
  pMatchingEntry_.clear();
  this->vPLabel_[this->index_ % this->entryNumber_]->set_name(CSS_INACTIVE_LABEL);

  if (this->entry_.get_text() == "") {
    for (int i = 0; i < this->vEntry_.size(); i++)
      this->pMatchingEntry_.push_back(std::pair<int, Iris::Entry>(0, this->vEntry_[i]));

  } else {
    Iris::Entry entry;
    int match = 0;

    for (int i = 0; i < this->vEntry_.size(); i++) {
      entry = this->vEntry_[i];
      match = common(entry.label, this->entry_.get_text());

      if (match != 0) this->pMatchingEntry_.push_back(std::pair<int, Iris::Entry>(match, entry));
    }
  }

  std::sort(this->pMatchingEntry_.begin(), this->pMatchingEntry_.end(), sort);

  if (this->index_ >= this->pMatchingEntry_.size()) this->index_ = this->pMatchingEntry_.size() - 1;
  if (this->pMatchingEntry_.size() != 0)
    this->vPLabel_[this->index_ % this->entryNumber_]->set_name(CSS_ACTIVE_LABEL);

  this->show_entrys();

  this->rightLabel_.set_text(std::to_string(this->pMatchingEntry_.size()) + "/" +
                             std::to_string(this->vEntry_.size()));

  return;
}

void Iris::Search::run()
{
  if (this->pMatchingEntry_.size() <= this->index_) return;

  std::string str = this->pMatchingEntry_[this->index_].second.command;
  if (!(str.find(" ") >= str.size())) str = str.erase(str.find(" "));

  system((str + " &").c_str());
  std::cout << LOG_RUN(str + " &") << std::endl;

  exit(0);

  return;
}
