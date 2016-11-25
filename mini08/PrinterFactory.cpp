#include <sstream>
#include "PrintJob.h"
#include "PrinterTypes.h"

#include "PrinterFactory.h"

// TODO: Implement PrinterFactory methods here.

PrinterFactory::PrinterFactory(unsigned resource)
    : m_resource(resource), m_printerCounter(0) {}

unsigned PrinterFactory::serialNumber = 0;

std::unique_ptr<Printer> PrinterFactory::makeDotMatrix() {
  std::stringstream ss;
  std::string serial;
  ss << "DOT-" << serialNumber++ << std::endl;
  std::getline(ss, serial);
  ++m_printerCounter;
  return std::make_unique<DotMatrix>(m_resource, serial);
}

std::unique_ptr<Printer> PrinterFactory::makeInkjet() {
  std::stringstream ss;
  std::string serial;
  ss << "INK-" << serialNumber++ << std::endl;
  std::getline(ss, serial);
  ++m_printerCounter;
  return std::make_unique<InkJet>(m_resource, serial);
}

std::unique_ptr<Printer> PrinterFactory::makeLaser() {
  std::stringstream ss;
  std::string serial;
  ss << "LSR-" << serialNumber++ << std::endl;
  std::getline(ss, serial);
  ++m_printerCounter;
  return std::make_unique<Laser>(m_resource, serial);
}

unsigned PrinterFactory::counter() const {
  return m_printerCounter;
}

void PrinterFactory::reset() {
  PrinterFactory::serialNumber = 0;
}
