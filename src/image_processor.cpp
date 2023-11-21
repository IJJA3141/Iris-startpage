#include "image_processor.hpp"

Iris::ImageProcessor::ImageProcessor(int _radius)
    : sum_(0), r_(0), g_(0), b_(0), kernel_size_((2 * _radius) + 1),
      kernel_(kernel_size_, std::vector<float>(this->kernel_size_))
{
  float σ = (float)_radius / 2;

  for (int x = -_radius; x <= _radius; x++)
    for (int y = -_radius; y <= _radius; y++)
      this->sum_ += this->kernel_[x + _radius][y + _radius] =
          std::exp(-std::sqrt(x * x + y * y) / (2 * σ * σ)) / (σ * sqrt(2 * M_PI));

  std::cout << "secfault" << std::endl;

  return;
}

/*
void test(Gdk::Rectangle _rect)
{
  std::vector<std::vector<float>> a = {
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 0
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 1
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 2
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 3
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 4
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 5
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 6
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 7
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 8
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 9
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 10
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 11
      {50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100, 100}, // 12
  };
  std::vector<std::vector<float>> b = a;
  float c = 0;

  int radius = this->kernel_size_ / 2;

  std::vector<std::vector<float>> aa = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}};

  _rect = {1, 1, 10, 10};

  for (int x = _rect.get_x(); x < _rect.get_width() + _rect.get_x(); x++) {
    if (x >= a[0].size()) break;
    for (int y = _rect.get_y(); y < _rect.get_height() + _rect.get_y(); y++) {
      if (y >= a[0].size()) break;

      for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
          if (0 <= x + i && x + i < a.size() && 0 <= y + j && y + j < a[0].size())
            c += a[x + i][y + j] * this->kernel_[i + radius][j + radius];

      c /= this->sum_;
      b[x][y] = c;
      c = 0;
    }
  }

  for (int x = 0; x < b.size(); x++) {
    for (int y = 0; y < b[0].size(); y++)
      std::cout << "|" << b[x][y] << "|";
    std::cout << "\n";
  }

  return;
};
*/

void Iris::ImageProcessor::blur(Glib::RefPtr<Gdk::Pixbuf> _pPixbuf, Gdk::Rectangle _rect)
{
  guint8 *pixels = _pPixbuf->get_pixels();
  int radius = this->kernel_size_ / 2;

  // Precaution
  if (!_pPixbuf) return;

  if (_pPixbuf->get_colorspace() != Gdk::Colorspace::RGB) return;
  if (_pPixbuf->get_bits_per_sample() != 8) return;

  // Iterate over the rectangle
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
