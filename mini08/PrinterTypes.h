#ifndef PRINTER_TYPES_H
#define PRINTER_TYPES_H

#include "PrintJob.h"
#include "Printer.h"

class DotMatrix : public Printer {
 private:
  unsigned int m_resource;
  const std::string m_serial;
  unsigned int m_pageCounter;

 public:
  DotMatrix(unsigned resource, const std::string& serial)
      : m_resource(resource), m_serial(serial), m_pageCounter(0) {}

  virtual const std::string& getSerial() const override;

  virtual unsigned int print(const PrintJob& job) override;

  virtual unsigned int pageCounter() const override;
};

class InkJet : public Printer {
 private:
  unsigned int m_resourceBlack;
  unsigned int m_resourceRGB;
  const std::string m_serial;
  unsigned int m_pageCounter;

 public:
  InkJet(unsigned resource, const std::string& serial)
      : m_resourceBlack(resource),
        m_resourceRGB(resource),
        m_serial(serial),
        m_pageCounter(0) {}

  virtual const std::string& getSerial() const override;

  virtual unsigned int print(const PrintJob& job) override;

  virtual unsigned int pageCounter() const override;
};

class Laser : public Printer {
 private:
  unsigned int m_resource;
  const std::string m_serial;
  unsigned int m_pageCounter;

 public:
  Laser(unsigned resource, const std::string& serial)
      : m_resource(resource), m_serial(serial), m_pageCounter(0) {}

  virtual const std::string& getSerial() const override;

  virtual unsigned int print(const PrintJob& job) override;

  virtual unsigned int pageCounter() const override;
};
#endif  // PRINTER_TYPES_H
