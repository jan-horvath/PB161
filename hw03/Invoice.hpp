//
// Created by Jan Horvath on 03-Dec-16.
//

#ifndef HW03_ACCOUNTING_INVOICE_HPP
#define HW03_ACCOUNTING_INVOICE_HPP

#include <vector>
#include "Subject.hpp"
#include "InvoiceItem.hpp"

class Invoice {
public:
    const unsigned int m_Id;
    const Subject m_supplier;
    const Subject m_buyer;
    const unsigned int m_variableCode;
    const unsigned int m_constantCode;
    const std::string m_invoiceDate;
    const std::string m_dueDate;
    const std::vector<InvoiceItem> m_items;

    Invoice(const unsigned int id, const Subject &m_supplier,
            const Subject &m_buyer, const unsigned int m_variableCode, const unsigned int m_constantCode,
            const std::string &m_invoiceDate, const std::string &m_dueDate, const std::vector<InvoiceItem> &m_items)
            : m_Id(id), m_supplier(m_supplier), m_buyer(m_buyer),
              m_variableCode(m_variableCode), m_constantCode(m_constantCode), m_invoiceDate(m_invoiceDate),
              m_dueDate(m_dueDate), m_items(m_items) {}
};

#endif //HW03_ACCOUNTING_INVOICE_HPP
