#ifndef FRAME

#include <gtkmm.h>

#define FRAME

namespace Iris {

class Frame : public Gtk::Widget {
protected:
  Gtk::Image img_;

public:
  Frame();
  virtual ~Frame();

protected:
  // Overrides:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_min,
                     int &_natural, int &_min_baseline,
                     int &_natural_baseline) const override;
  void on_map() override;
  void on_unmap() override;
  void on_realize() override;
  void on_unrealize() override;
};
} // namespace Iris
#endif // !FRAME
