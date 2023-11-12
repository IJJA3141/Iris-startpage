#ifndef IMAGE_PROCESSOR

#include "cairomm/surface.h"
#include "gdkmm/rectangle.h"
#include <cmath>
#include <iostream>
#include <vector>

#define IMAGE_PROCESSOR

namespace Iris
{
class ImageProcessor
{
private:
  int kernel_size_;
  std::vector<std::vector<float> > kernel_;
  float sum_;

public:
  ImageProcessor (int _radius);

  void blur (Cairo::Surface *_cs, Gdk::Rectangle _rect);
};
}

#endif // !IMAGE_PROCESSOR
