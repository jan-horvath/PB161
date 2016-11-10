#include "image.hpp"

#ifndef TOOLS_HPP
#define TOOLS_HPP

// rotation direction
enum Direction { D_Left, D_Right };

Image rotate(Image& img, Direction direction);
Image grayscale(Image& img, const std::string& channels);
Image pad(Image& img,
          unsigned top,
          unsigned left,
          unsigned bottom,
          unsigned right,
          Pixel& fill);
Image cut(Image& img, unsigned x, unsigned y, unsigned width, unsigned height);

#endif  // TOOLS_HPP
