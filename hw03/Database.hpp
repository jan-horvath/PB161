//
// Created by Jan Horvath on 03-Dec-16.
//

#ifndef HW03_ACCOUNTING_DATABASE_HPP
#define HW03_ACCOUNTING_DATABASE_HPP

#include "Subject.hpp"
#include "Invoice.hpp"
#include <memory>

class Database {
 private:
  std::vector<std::unique_ptr<Invoice>> m_invoices;
  std::vector<std::unique_ptr<Subject>> m_subjects;

 public:
  bool addInvoice(const Invoice& invoice);

  Invoice const* getInvoice(unsigned id) const;

  bool addSubject(const Subject& subject);

  Subject const* getSubject(unsigned id) const;

  bool updateSubject(const Subject& subject);

  std::vector<Invoice const*> getInvoicesByCustomer(unsigned int customerId);

  std::vector<Invoice const*> getInvoicesBySupplier(unsigned int supplierId);

  bool containsSubject(unsigned id);

  bool containsInvoice(unsigned id);
};

#endif  // HW03_ACCOUNTING_DATABASE_HPP
