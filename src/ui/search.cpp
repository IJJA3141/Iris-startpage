#include "search.hpp"
#include "../const/css.hpp"
#include "../const/label.hpp"
#include "../lua/config.hpp"

#include <algorithm>
#include <iostream>

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

bool comaperEntry(std::pair<int, Iris::Entry *> &_, std::pair<int, Iris::Entry *> &__)
{
  return (_.first < __.first);
}

int edit_distance(std::string _compared, std::string _comparing)
{
  uint16_t arr[_compared.size() + 1][_comparing.size() + 1];

  for (uint16_t i = 0; i <= _compared.size(); i++)
    arr[i][0] = i;
  for (uint16_t i = 0; i <= _comparing.size(); i++)
    arr[0][i] = i;

  for (uint16_t i = 1; i <= _compared.size(); i++)
    for (uint16_t j = 1; j <= _comparing.size(); j++) {
      if (_compared[i - 1] == _comparing[j - 1])
        arr[i][j] = arr[i - 1][j - 1];
      else
        arr[i][j] = std::min({arr[i - 1][j - 1], arr[i][j - 1], arr[i - 1][j]}) + 1;
    }

  return (int)arr[_compared.size()][_comparing.size()];
}

void Iris::Search::match()
{

  if (this->entry_.get_text().size() == 0) {
    for (int i = 0; i < this->vEntry_.size(); i++)
      this->pMatchingEntry_.push_back(std::pair<int, Iris::Entry *>(0, &this->vEntry_[i]));

    return;
  }

  int distance;

  this->pMatchingEntry_.clear();

  for (int i = 0; i < this->vEntry_.size(); i++) {
    distance = edit_distance(this->vEntry_[i].label, this->entry_.get_text());

    std::cout << this->vEntry_[i].label << " : " << distance << std::endl;

    if (distance != std::max({this->vEntry_[i].label.size(), this->entry_.get_text().size()}))
      this->pMatchingEntry_.push_back(std::pair<int, Iris::Entry *>(distance, &this->vEntry_[i]));
  }

  std::sort(this->pMatchingEntry_.begin(), this->pMatchingEntry_.end(), comaperEntry);

  return;
};

bool Iris::Search::on_key_down(guint _keyval, guint _keycode, Gdk::ModifierType _state)
{
  if (_keyval == GDK_KEY_Escape) {
    this->get_parent()->grab_focus();
    return false;
  } else if (_keyval == GDK_KEY_Tab || _keyval == GDK_KEY_ISO_Left_Tab) {
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

  for (int i = 0; i < this->entryNumber_; i++) {
    if (i + indexFirst * this->entryNumber_ >= this->pMatchingEntry_.size()) break;

    this->vPLabel_[i]->set_text(
        this->pMatchingEntry_[i + indexFirst * this->entryNumber_].second->label);
  }

  return;
}
