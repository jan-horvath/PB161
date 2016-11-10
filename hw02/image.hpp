#include <cassert>
#include <iostream>
#include <stdint.h>
#include <vector>

#ifndef IMAGE_HPP
#define IMAGE_HPP

// **members should not be changed**
struct Pixel {
  uint8_t r, g, b, a;
};

// Represents image which is a 2D matrix of Pixels
// **existing interface should not be broken**
struct Image {
  Image() : _width(0), _height(0) {}
  Image(size_t width, size_t height);
  Image(const Image&);
  Image& operator=(const Image&);

  // this is only for debugging image transformations
  void dump(std::ostream& = std::cerr) const;

  Pixel& pixel(size_t x, size_t y) { return _data.at(y * _width + x); }

  Pixel pixel(size_t x, size_t y) const { return _data.at(y * _width + x); }

  bool valid() const {
    assert((_width == 0) == (_height == 0) && (_data.empty()) == (_width == 0));
    return !_data.empty();
  }

  unsigned width() const { return _width; }
  unsigned height() const { return _height; }

 private:
  std::vector<Pixel> _data;
  size_t _width, _height;
};

const Image decodePNG(const std::string& filename);
bool encodePNG(const std::string& filename, const Image& img);

#endif  // IMAGE_HPP
