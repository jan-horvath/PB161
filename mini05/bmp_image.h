#include "bmp/bmp.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class BMPImage {
public:
  BMPImage(const std::string &name);
  BMPImage(uint16_t width, uint16_t height,
           const std::string &name = std::string(""));
  BMPImage(const BMPImage &other);
  BMPImage &operator=(const BMPImage &other);
  ~BMPImage();
  uint16_t width() const;
  uint16_t height() const;
  const std::string &filename() const;
  bool good() const;
  const Pixel &getPixel(uint16_t x, uint16_t y) const;
  bool setPixel(uint16_t x, uint16_t y, Pixel p);
  void setFilename(const std::string &name);

private:
  std::string m_name;
  uint16_t m_width;
  uint16_t m_height;
  std::unique_ptr<Pixel[]> m_pixels;
  bool m_isGood;
};
