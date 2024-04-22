#include "search.hpp"
#include "../const/label.hpp"
#include "../lua/config.hpp"

#include <string>

Iris::Search::Search()
    : index_(0), searchBox_(Gtk::Orientation::HORIZONTAL), leftLabel_(SEARCH_LEFT_LABEL),
      vEntry_(Iris::xdg::fetch())
{
  this->rightLabel_.set_text("0/" + std::to_string(this->vEntry_.size()));

  this->searchBox_.append(this->entry_);
  this->searchBox_.insert_at_start(this->leftLabel_);
  this->searchBox_.insert_at_end(this->rightLabel_);
  this->entry_.set_expand(true);

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

void Iris::Search::match(const std::string _entryName) {

  return; 
};
