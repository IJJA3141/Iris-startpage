#include "image_processor.hpp"
#include "gdkmm/pixbuf.h"

Iris::ImageProcessor::ImageProcessor(int _radius)
    : sum_(0), r_(0), g_(0), b_(0), kernel_size_(2 * _radius + 1)
{
  this->kernel_ =
      std::vector<std::vector<float>>(this->kernel_size_, std::vector<float>(this->kernel_size_));

  float σ = (float)_radius / 2;

  for (int x = -_radius; x <= _radius; x++)
    for (int y = -_radius; y <= _radius; y++)
      this->sum_ += this->kernel_[x + _radius][y + _radius] =
          std::exp(-std::sqrt(x * x + y * y) / (2 * σ * σ)) / (σ * sqrt(2 * M_PI));

  return;
}

void Iris::ImageProcessor::blur(Glib::RefPtr<Gdk::Pixbuf> _pPixbuf, Gdk::Rectangle _rect)
{
  // Precautions
  if (!_pPixbuf) return;

  if (_pPixbuf->get_colorspace() != Gdk::Colorspace::RGB) return;
  if (_pPixbuf->get_bits_per_sample() != 8) return;

  // Get data
  guint8 *pixels = _pPixbuf->get_pixels();
  int radius = this->kernel_size_ / 2;

  // Iterate over _rect
  for (int x = _rect.get_x(); x < _rect.get_width() + _rect.get_x(); x++) {
    if (x >= _pPixbuf->get_width()) break;
    for (int y = _rect.get_y(); y < _rect.get_height() + _rect.get_y(); y++) {
      if (y >= _pPixbuf->get_height()) break;

      // Iterate over the kernel
      for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j < radius; j++) {
          this->r_ += (&pixels[(x + i) * _pPixbuf->get_n_channels() +
                               (y + j) * _pPixbuf->get_rowstride()])[0] *
                      this->kernel_[i + radius][j + radius];
          this->g_ += (&pixels[(x + i) * _pPixbuf->get_n_channels() +
                               (y + j) * _pPixbuf->get_rowstride()])[1] *
                      this->kernel_[i + radius][j + radius];
          this->b_ += (&pixels[(x + i) * _pPixbuf->get_n_channels() +
                               (y + j) * _pPixbuf->get_rowstride()])[2] *
                      this->kernel_[i + radius][j + radius];
        }

      this->r_ /= this->sum_;
      this->g_ /= this->sum_;
      this->b_ /= this->sum_;

      (&pixels[x * _pPixbuf->get_n_channels() + y * _pPixbuf->get_rowstride()])[0] = this->r_;
      (&pixels[x * _pPixbuf->get_n_channels() + y * _pPixbuf->get_rowstride()])[1] = this->g_;
      (&pixels[x * _pPixbuf->get_n_channels() + y * _pPixbuf->get_rowstride()])[2] = this->b_;

      this->r_ = 0;
      this->g_ = 0;
      this->b_ = 0;
    }
  }

  return;
};
