#include "image.hpp"
#include <iomanip>
#include <lodepng.h>

const Image decodePNG(const std::string &filename) {
  std::vector<unsigned char> data;
  unsigned width, height;
  unsigned error = lodepng::decode(data, width, height, filename);
  if (error) {
    std::cerr << "error decoding " << filename << ": "
              << lodepng_error_text(error) << std::endl;
    return Image();
  }

  Image img = Image(width, height);
  std::vector<unsigned char>::iterator it = data.begin();
  for (unsigned j = 0; j < height; ++j) {
    for (unsigned i = 0; i < width; ++i) {
      Pixel &px = img.pixel(i, j);
      px.r = *(it++);
      px.g = *(it++);
      px.b = *(it++);
      px.a = *(it++);
    }
  }
  assert(it == data.end());
  return img;
}

bool encodePNG(const std::string &filename, const Image &img) {
  std::vector<unsigned char> data;
  for (unsigned j = 0; j < img.height(); ++j) {
    for (unsigned i = 0; i < img.width(); ++i) {
      data.push_back(img.pixel(i, j).r);
      data.push_back(img.pixel(i, j).g);
      data.push_back(img.pixel(i, j).b);
      data.push_back(img.pixel(i, j).a);
    }
  }

  unsigned error = lodepng::encode(filename, data, img.width(), img.height());

  if (error)
    std::cerr << "error encoding " << filename << ":"
              << lodepng_error_text(error) << std::endl;
  return !error;
}

void Image::dump(std::ostream &os) const {
  os << std::hex << std::setfill('0');
  for (unsigned j = 0; j < _height; ++j) {
    for (unsigned i = 0; i < _width; ++i) {
      Pixel px = pixel(i, j);
      os << std::setw(2) << +px.r // unary plus here changes char to int
         << std::setw(2) << +px.g // so it can be printed as number
         << std::setw(2) << +px.b << std::setw(2) << +px.a << " ";
    }
    os << std::endl;
  }
}

Image::Image(size_t width, size_t height) : _width(width), _height(height) {
  _data.resize(width * height);
}

Image::~Image() {
  // delete _data;
  // causes SEGV sometimes :-\
    // for some reason we need empty line or comment here before }
}

Image::Image(const Image &o)
    : _data(o._data), _width(o._width), _height(o._height) {}

Image &Image::operator=(const Image &o) {
  _data.resize(o._height * o._width);
  _data.clear();
  std::copy(o._data.begin(), o._data.end(), std::back_inserter(_data));
  _width = o._width;
  _height = o._height;
  return *this;
}
