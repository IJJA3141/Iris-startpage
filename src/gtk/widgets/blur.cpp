#include "gif.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

//
// 1 / ( 2πσ^2) * e^( -(x^2 + y^2) / (2σ^2))
//

void
Iris::Pane::blur (Cairo::Surface *_pCs, Cairo::Rectangle _rect, int _radius)
{
  int σ = 1;
  int value;

  std::vector<std::vector<int> > kernel;

  for (int i = 0; i < (2 * _radius) + 1; i++)
    kernel.push_back (std::vector<int> ((2 * _radius) + 1));

  float sum = 0.0;

  for (int x = -_radius; x <= _radius; x++)
    {
      for (int y = -_radius; y <= _radius; y++)
        {
          value = exp ((double)-(x * x + y * y) / (2 * σ * σ)) / (2 * M_PI * σ * σ);

          kernel[x + _radius][y + _radius] = value;
          sum += value;
        }
    }

  for (int i = 0; i < kernel.size (); i++)
    {
      for (int j = 0; j < kernel.size (); j++)
        kernel[i][j] /= sum;
    }

  

  return;
};
