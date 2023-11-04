#ifndef LEFT

#include <gtkmm.h>

#define LEFT

namespace Up {
class Left : public Gtk::Widget {
private:
  Gtk::Image *img_;
  Gtk::Label *label_;

public:
  Left();
  virtual ~Left();

  void set_childs(Gtk::Image &_img, Gtk::Label &_label);

protected:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void measure_vfunc(Gtk::Orientation orientation, int for_size, int &minimum,
                     int &natural, int &minimum_baseline,
                     int &natural_baseline) const override;
  void size_allocate_vfunc(int width, int height, int baseline) override;
};
}; // namespace Up

#endif // !LEFT
