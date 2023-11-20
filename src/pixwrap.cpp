#include "pixwrap.hpp"
#include <cstdlib>

Iris::Pixwrap::Pixwrap(Glib::RefPtr<Gdk::Pixbuf> _pPixbuf)
    : RGBMatrix_(_pPixbuf->get_width(), std::vector<std::array<uint8_t, 3>>(
                                            _pPixbuf->get_height(), std::array<uint8_t, 3>()))
{
  int offset = 0;
  guchar *pixel = nullptr;

  for (int x = 0; x < _pPixbuf->get_width(); x++)
    for (int y = 0; y < _pPixbuf->get_height(); y++) {
      offset = y * _pPixbuf->get_rowstride() + x * _pPixbuf->get_n_channels();
      pixel = &_pPixbuf->get_pixels()[offset];

      this->RGBMatrix_[x][y][0] = pixel[0];
      this->RGBMatrix_[x][y][1] = pixel[1];
      this->RGBMatrix_[x][y][2] = pixel[2];
    }

  return;
}

void Iris::Pixwrap::debug()
{
  for (int x = 0; x < this->RGBMatrix_.size(); x++) {
    for (int y = 0; y < this->RGBMatrix_[0].size(); y++)
      std::cout << "|R: " << this->RGBMatrix_[x][y][0] << " |G: " << this->RGBMatrix_[x][y][1]
                << " |B: " << this->RGBMatrix_[x][y][2];
    std::cout << "\n";
  }

  abort();

  return;
}
