#ifndef IMAGE_PROCESSOR
#define IMAGE_PROCESSOR

#include <gtkmm.h>
#include <vector>

namespace Iris
{

class ImageProcessor
{
private:
  std::vector<std::vector<float>> kernel_;
  int kernel_size_;
  float sum_;
  float r_;
  float g_;
  float b_;

public:
  ImageProcessor(int _radius);

  void blur(Glib::RefPtr<Gdk::Pixbuf> _pPixbuf, Gdk::Rectangle _rect);
};
} // namespace Iris

#endif // !IMAGE_PROCESSOR
