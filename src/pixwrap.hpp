#ifndef PIXWRAP
#define PIXWRAP

#include "gdkmm/pixbuf.h"
#include "glibmm/refptr.h"
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

namespace Iris
{

class Pixwrap
{
private:
  std::vector<std::vector<std::array<uint8_t, 3>>> RGBMatrix_;

public:
  Pixwrap(Glib::RefPtr<Gdk::Pixbuf> _pPixbuf);

  void debug();
private:
};
}; // namespace Iris

#endif // !PIXWRAP
