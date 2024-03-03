#ifndef _IRIS_WINDOW
#define _IRIS_WINDOW

#include <gtkmm.h>

namespace Iris
{
class Window : public Gtk::Window
{
public:
  Window();
  Gtk::Label lb;

private:
};
} // namespace Iris

#endif // !_IRIS_WINDOW
