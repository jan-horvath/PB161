#include "bmp_image.h"
#include <iostream>

BMPImage::BMPImage(const std::string &name) : m_name(name) {
  if (readBMPSize(name.c_str(), m_width, m_height)) {
    m_pixels = std::make_unique<Pixel[]>(m_width * m_height);
    readBMP(name.c_str(), m_pixels.get());
    m_isGood = true;
    return;
  }
  m_isGood = false;
}

BMPImage::BMPImage(uint16_t width, uint16_t height, const std::string &name)
    : m_name(name), m_width(width), m_height(height), m_isGood(true) {
  m_pixels = std::make_unique<Pixel[]>(m_height * m_width);
}

BMPImage::BMPImage(const BMPImage &other)
    : m_isGood(true), m_height(other.m_height), m_width(other.m_width) {
  auto pixelsPointer = std::make_unique<Pixel[]>(m_height * m_width);
  std::copy(other.m_pixels.get(),
            other.m_pixels.get() + other.m_width * other.m_height,
            pixelsPointer.get());
  m_pixels = std::move(pixelsPointer);
}

BMPImage &BMPImage::operator=(const BMPImage &other) {
  m_height = other.m_height;
  m_width = other.m_width;
  auto pixelsPointer = std::make_unique<Pixel[]>(m_height * m_width);
  std::copy(other.m_pixels.get(),
            other.m_pixels.get() + other.m_width * other.m_height,
            pixelsPointer.get());
  m_pixels = std::move(pixelsPointer);
  m_isGood = true;
  return *this;
}

BMPImage::~BMPImage() {
  if ((!m_name.empty()) && (m_isGood)) {
    if (!writeBMP(m_name.c_str(), m_width, m_height, m_pixels.get())) {
      std::cerr << "Error while writing file " << m_name << std::endl;
    }
  }
}

uint16_t BMPImage::width() const { return m_width; }

uint16_t BMPImage::height() const { return m_height; }

const std::string &BMPImage::filename() const { return m_name; }

bool BMPImage::good() const { return m_isGood; }

const Pixel &BMPImage::getPixel(uint16_t x, uint16_t y) const {
  if ((y >= m_height) || (x >= m_width))
    return *m_pixels.get();
  return *(m_pixels.get() + y * m_width + x);
}

bool BMPImage::setPixel(uint16_t x, uint16_t y, Pixel p) {
  if ((y >= m_height) || (x >= m_width))
    return false;
  *(m_pixels.get() + y * m_width + x) = p;
  return true;
}

void BMPImage::setFilename(const std::string &name) { m_name = name; }
