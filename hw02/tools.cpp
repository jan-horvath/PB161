#include "tools.hpp"
#include "die.hpp"
#include <cstdlib>

Image rotate(Image &img, Direction direction) {
  Image rotated(img.height(), img.width());
  for (unsigned j = 0; j < rotated.height(); ++j)
    for (unsigned i = 0; i < rotated.width(); ++i)
      if (direction == Direction::D_Left)
        rotated.pixel(i, j) = img.pixel(img.width() - j - 1, i);
      else if (direction == Direction::D_Right)
        rotated.pixel(i, j) = img.pixel(j, img.height() - i - 1);
  return rotated;
}

Image grayscale(Image &img, const std::string &channels) {
  if (channels.length() > 3)
    die("too many channels entered");
  std::string nonEmptyChannels = channels;
  if (nonEmptyChannels.empty()) {
    nonEmptyChannels = "rgb";
  }
  bool rChannel = false;
  bool gChannel = false;
  bool bChannel = false;
  for (char channel : nonEmptyChannels) {
    if (channel == 'r')
      rChannel = true;
    else if (channel == 'g')
      gChannel = true;
    else if (channel == 'b')
      bChannel = true;
  }

  if ((rChannel + gChannel + bChannel) < nonEmptyChannels.length())
    die("Repeating or invalid channels");

  for (unsigned j = 0; j < img.height(); ++j)
    for (unsigned i = 0; i < img.width(); ++i) {
      int average = 0;
      if (rChannel)
        average += img.pixel(i, j).r;
      if (gChannel)
        average += img.pixel(i, j).g;
      if (bChannel)
        average += img.pixel(i, j).b;
      average = average / nonEmptyChannels.length();
      img.pixel(i, j).r = img.pixel(i, j).g = img.pixel(i, j).b = average;
    }
  return img;
}

Image pad(Image &img, unsigned top, unsigned left, unsigned bottom,
          unsigned right, Pixel &fill) {
  Image padded(img.width() + left + right, img.height() + top + bottom);
  for (unsigned j = 0; j < padded.height(); ++j)
    for (unsigned i = 0; i < padded.width(); ++i)
      if (j < top || j >= top + img.height() || i < left ||
          i >= left + img.width()) {
        padded.pixel(i, j) = fill;
      } else
        padded.pixel(i, j) = img.pixel(i - left, j - top);
  return padded;
}

Image cut(Image &img, unsigned x, unsigned y, unsigned width, unsigned height) {
  if ((x + width) > img.width() || width == 0)
    width = img.width() - x;
  if ((y + height) > img.height() || height == 0)
    height = img.height() - y;
  Image cut(width, height);
  for (unsigned j = 0; j < cut.height(); ++j)
    for (unsigned i = 0; i < cut.width(); ++i)
      cut.pixel(i, j) = img.pixel(i + x, j + y);
  return cut;
}
