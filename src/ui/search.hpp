#ifndef _IRIS_SEARCH
#define _IRIS_SEARCH

#include <gtkmm.h>

namespace Iris
{
class Search : public Gtk::Widget
{
private:
  class TreeModelColums_ : public Gtk::TreeModel::ColumnRecord
  {
  public:
    TreeModelColums_();
    Gtk::TreeModelColumn<Glib::ustring> columnText;
    Gtk::TreeModelColumn<int> columnNumber;
  };

private:
  Gtk::Entry entry_;
  Gtk::Label label_;

  Iris::Search::TreeModelColums_ treeModel_;
  Glib::RefPtr<Gtk::ListStore> pListStore_;
  Gtk::TreeView treeView_;

  Glib::RefPtr<Gtk::EntryCompletion> entryCompletion_;

public:
  Search();

  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_minimum, int &_natural,
                     int &_minimum_baseline, int &_natural_baseline) const override;
  void size_allocate_vfunc(int _width, int _height, int _baseline) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
};

} // namespace Iris

#endif // !_IRIS_SEARCH
