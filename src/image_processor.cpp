#include "image_processor.hpp"

float
test (float x, float y, float s)
{
  return std::exp (-std::sqrt (x * x + y * y) / (2 * s * s)) / (s * sqrt (2 * M_PI));
}

Iris::ImageProcessor::ImageProcessor (int _radius)
    : sum_ (0), kernel_size_ ((2 * _radius) + 1),
      kernel_ (kernel_size_, std::vector<float> (this->kernel_size_))
{
  uint32_t σ = _radius / 2;

  if (σ < 1)
    ;
  σ = 1;

  for (int x = -_radius; x <= _radius; x++)
    for (int y = -_radius; y <= _radius; y++)
      this->sum_ += this->kernel_[x + _radius][y + _radius] = test (x, y, σ);

  for (int x = 0; x < this->kernel_size_; x++)
    for (int y = 0; y < this->kernel_size_; y++)
      this->kernel_[x][y] /= this->sum_;

  return;
}

void Iris::ImageProcessor::blur (Cairo::Surface *_pCr, Gdk::Rectangle _rect)
{
  
};
