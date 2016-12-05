#ifndef HW03_ACCOUNTING_INVOICE_ITEM_H
#define HW03_ACCOUNTING_INVOICE_ITEM_H

#include <string>

/**
 * You can modify this file a little bit, but keep the provided constructor,
 * it's neccesary.
 */
class InvoiceItem {
  std::string title;
  unsigned amount;
  unsigned taxRate;

 public:
  InvoiceItem(const std::string& title, unsigned amount, unsigned taxRate)
      : title(title), amount(amount), taxRate(taxRate) {}

  const std::string& getTitle() const { return title; }

  unsigned getAmount() const { return amount; }

  unsigned getTaxRate() const { return taxRate; }
};

#endif  // HW03_ACCOUNTING_INVOICE_ITEM_H
