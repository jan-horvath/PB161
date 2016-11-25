#include "PrinterTypes.h"

// TODO: Implement your printers here
// DotMatrix

const std::string& DotMatrix::getSerial() const {
  return m_serial;
}

unsigned int DotMatrix::print(const PrintJob& job) {
  if (m_resource == 0)
    return 0;
  unsigned int pagesPrinted = 0;
  for (unsigned int i = 0; i < job.copies; ++i) {
    if (m_resource == 0)
      break;
    for (auto page : job.pages) {
      if ((page == Page::PlainText) || (page == Page::RichText) ||
          (page == Page::Mixed)) {
        if (m_resource > 0) {
          --m_resource;
          ++pagesPrinted;
        }
      }
    }
  }
  m_pageCounter += pagesPrinted;
  return pagesPrinted;
}

unsigned int DotMatrix::pageCounter() const {
  return m_pageCounter;
}

//-------------------------------------------------------
// InkJet

bool checkInk(unsigned blackNeeded,
              unsigned RGBNeeded,
              unsigned blackAvailable,
              unsigned RGBAvailable) {
  return (blackNeeded <= blackAvailable) && (RGBNeeded <= RGBAvailable);
}

const std::string& InkJet::getSerial() const {
  return m_serial;
}

unsigned int InkJet::print(const PrintJob& job) {
  unsigned int pagesPrinted = 0;
  bool failedToPrint = false;
  for (unsigned int i = 0; i < job.copies; ++i) {
    for (auto page : job.pages) {
      switch (page) {
        case Page::PlainText: {
          if (checkInk(1, 0, m_resourceBlack, m_resourceRGB)) {
            --m_resourceBlack;
            ++pagesPrinted;
          } else
            failedToPrint = true;
          break;
        }
        case Page::RichText: {
          if (checkInk(1, 1, m_resourceBlack, m_resourceRGB)) {
            --m_resourceBlack;
            --m_resourceRGB;
            ++pagesPrinted;
          } else
            failedToPrint = true;
          break;
        }
        case Page::Picture: {
          if (checkInk(0, 2, m_resourceBlack, m_resourceRGB)) {
            m_resourceRGB -= 2;
            ++pagesPrinted;
          } else
            failedToPrint = true;
          break;
        }
        case Page::Mixed: {
          if (checkInk(1, 2, m_resourceBlack, m_resourceRGB)) {
            --m_resourceBlack;
            m_resourceRGB -= 2;
            ++pagesPrinted;
          } else
            failedToPrint = true;
          break;
        }
      }
      if (failedToPrint)
        break;
    }
    if (failedToPrint)
      break;
  }
  m_pageCounter += pagesPrinted;
  return pagesPrinted;
}

unsigned int InkJet::pageCounter() const {
  return m_pageCounter;
}

//--------------------------------------------------------
// Laser

const std::string& Laser::getSerial() const {
  return m_serial;
}

unsigned int Laser::print(const PrintJob& job) {
  unsigned pagesPrinted = 0;
  for (unsigned i = 0; i < job.copies; ++i) {
    for (auto page : job.pages) {
      if ((page == Page::PlainText) || (page == Page::RichText) ||
          (page == Page::Mixed)) {
        if (m_resource >= 1) {
          --m_resource;
          ++pagesPrinted;
        } else {
          m_pageCounter += pagesPrinted;
          return pagesPrinted;
        }
      }
      if (page == Page::Picture) {
        if (m_resource >= 2) {
          m_resource -= 2;
          ++pagesPrinted;
        } else {
          m_pageCounter += pagesPrinted;
          return pagesPrinted;
        }
      }
    }
  }
  m_pageCounter += pagesPrinted;
  return pagesPrinted;
}

unsigned int Laser::pageCounter() const {
  return m_pageCounter;
}
