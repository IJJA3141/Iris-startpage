#ifndef IMAGE  

#include <gtkmm.h>

#define IMAGE 

namespace Up {

class Image : public Gtk::Widget {
public:
  Image();
  ~Image() override;

protected:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void measure_vfunc(Gtk::Orientation _orientation, int _for_size, int &_min,
                     int &_natural, int &_min_baseline,
                     int &_natural_baseline) const override;

  void on_map() override;
  void on_unmap() override;
  void on_realize() override;
  void on_unrealize() override;
  void snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &snapshot) override;

  Gtk::Border padding_;
};
} // namespace Up

#endif // !IMAGE
