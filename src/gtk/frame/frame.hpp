#include "gtkmm/image.h"
#ifndef FRAME

#include <gtkmm.h>

#include "left.hpp"
#include "right.hpp"

#define FRAME

namespace Up {

class Frame : public Gtk::Widget {
public:
  Frame();
  virtual ~Frame();

protected:
  Up::Left left_;
  Up::Right right_;

  Gtk::Image img_;
  Gtk::Label label_;
};
};     // namespace Up
#endif // !FRAME
