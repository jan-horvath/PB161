#ifndef PRINTER_FACTORY_H
#define PRINTER_FACTORY_H

#include <memory>
#include "Printer.h"

class PrinterFactory {
 private:
  static unsigned serialNumber;
  unsigned m_resource;
  unsigned m_printerCounter;

 public:
  /**
   * Creates a factory.
   * @param   resource        default printer resource size
   */
  PrinterFactory(unsigned resource);

  /**
   * Constructs a Dot Matrix Printer
   */
  std::unique_ptr<Printer> makeDotMatrix();

  /**
   * Constructs an Inkjet Printer
   */
  std::unique_ptr<Printer> makeInkjet();

  /**
   * Constructs a Laser Printer
   */
  std::unique_ptr<Printer> makeLaser();

  /**
   * Returns the number of printers this factory has ever created.
   */
  unsigned counter() const;

  /**
   * Resets the serial number generator.
   */
  void reset();
};

#endif  // PRINTER_FACTORY_H
