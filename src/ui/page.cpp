#include "page.hpp"
#include "../const/css.hpp"

Iris::Page::Page(const Iris::Config::Page &_page)
    : title_(_page.name), box_(Gtk::Orientation::VERTICAL)
{
  for (int i = 0; i < 3; i++) {
    this->aRow_[i] = new Iris::Row(_page.aRow[i]);
    this->aRow_[i]->set_name(CSS_PAGE_ROW);
    this->box_.append(*this->aRow_[i]);
  }

  this->title_.set_parent(*this);
  this->box_.set_parent(*this);

  return;
}

void Iris::Page::size_allocate_vfunc(int _width, int _height, int _baseline)
{
  Gtk::Allocation title, box;
  int minimum, natural, minimumBaseline, naturalBaseline;

  this->title_.measure(Gtk::Orientation::VERTICAL, _width, minimum, natural, minimumBaseline,
                       naturalBaseline);

  title.set_x(0);
  title.set_y(0);
  title.set_width(_width);
  title.set_height(minimum);

  box.set_x(0);
  box.set_y(minimum);
  box.set_width(_width);
  box.set_height(_height - minimum);

  this->title_.size_allocate(title, _baseline);
  this->box_.size_allocate(box, _baseline);

  return;
}

Iris::Row::Row(const Iris::Config::Row &_row)
    : title_(_row.title, Gtk::Align::START), box_(Gtk::Orientation::HORIZONTAL)
{
  Gtk::Button *pButton;

  for (int i = 0; i < _row.vButton.size(); i++) {
    pButton = new Gtk::Button(_row.vButton[i].label);

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

  this->title_.size_allocate(title, _baseline);
  this->box_.size_allocate(box, _baseline);

  return;
}
