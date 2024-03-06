#include "search.hpp"
#include "../xdg.hpp"
#include "gtkmm/entrycompletion.h"
#include <iostream>

Iris::Search::TreeModelColums_::TreeModelColums_()
{
  add(this->columnText);
  add(this->columnNumber);

  return;
};

Iris::Search::Search()
    : entry_(), treeModel_(), pListStore_(Gtk::ListStore::create(this->treeModel_)),
      treeView_(this->pListStore_), entryCompletion_(Gtk::EntryCompletion::create())
{
  Gtk::TreeModel::Row row;

  for (Iris::xdg::DesktopApplication app : Iris::xdg::fetch()) {
    row = *this->pListStore_->append();
    row[this->treeModel_.columnText] = app.name;
  }

  this->pListStore_->append();

  // css class asignation

  // parenting
  this->label_.set_parent(*this);
  this->entry_.set_parent(*this);
  this->treeView_.set_parent(*this);

  this->treeView_.append_column("", this->treeModel_.columnText);
  this->entryCompletion_->set_model(this->pListStore_);
  this->entry_.set_completion(this->entryCompletion_);
  this->entryCompletion_->set_text_column(this->treeModel_.columnText);
  this->entryCompletion_->set_minimum_key_length(1);

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
  Gtk::Allocation entry, tree, label;

  int min, nat, minBaseline, natBaseline;

  this->entry_.measure(Gtk::Orientation::VERTICAL, _width, min, nat, minBaseline, natBaseline);

  entry.set_x(0);
  entry.set_y(0);

  entry.set_height(min);
  label.set_height(min);

  tree.set_x(0);
  tree.set_y(min);
  tree.set_width(_width);
  tree.set_height(_height - min);

  this->label_.measure(Gtk::Orientation::HORIZONTAL, min, min, nat, minBaseline, natBaseline);

  entry.set_width(_width - min);

  label.set_y(0);
  label.set_x(_width - min);
  label.set_width(min);

  this->entry_.size_allocate(entry, _baseline);
  this->label_.size_allocate(label, _baseline);
  this->treeView_.size_allocate(tree, _baseline);

  return;
}

Gtk::SizeRequestMode Iris::Search::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::CONSTANT_SIZE;
}
