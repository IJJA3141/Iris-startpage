#ifndef BACKGROUND

#include <gtkmm.h>

#include "../../macros.hpp"
#include "../widgets/frame.hpp"

#define BACKGROUND

namespace Iris {

class Background : public Gtk::Window {
private:
  Iris::Frame frame_;

public:
  Background();

private:
};

} // namespace Iris

#endif // !BACKGROUND
