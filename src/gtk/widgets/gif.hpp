#ifndef GIF

#include <gtkmm.h>
#include <iostream>
#include <string>

#define GIF

namespace Iris {
class Pane : public Gtk::Widget {
public:
  static Cairo::RefPtr<Cairo::Context> cr_;
  static Glib::RefPtr<Gdk::PixbufAnimationIter> buff_;

private:
  Gtk::Border padding_;
  std::string label_;

public:
  Pane(std::string _label, std::string _image_path);

protected:
  void snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &_snapshot) override;
  void measure_vfunc(Gtk::Orientation _orientation, int _for_size,
                     int &_minimum, int &_natural, int &_minimum_baseline,
                     int &_natural_baseline) const override;
  void on_realize() override;

private:
  static bool draw_image();
};
} // namespace Iris

#endif // !GIF
