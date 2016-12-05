#ifndef HW03_ACCOUNTING_SERVICE_CONTAINER_INTERFACE_H
#define HW03_ACCOUNTING_SERVICE_CONTAINER_INTERFACE_H

#include "InvoiceFacadeInterface.hpp"
#include "SubjectsFacadeInterface.hpp"

/**
 * DO NOT MODIFY this file, Kontr will ignore the changes anyway.
 */
class ServiceContainerInterface {
 public:
  virtual ~ServiceContainerInterface() = default;

  virtual InvoiceFacadeInterface& getInvoiceFacade() = 0;
  virtual SubjectsFacadeInterface& getSubjectsFacade() = 0;
};

#endif  // HW03_ACCOUNTING_SERVICE_CONTAINER_INTERFACE_H
