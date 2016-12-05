//
// Created by Jan Horvath on 03-Dec-16.
//

#include "InvoiceFacade.hpp"
#include <cassert>

unsigned int
InvoiceFacade::createInvoice(unsigned supplierId, unsigned customerId, unsigned variableSymbol, unsigned constantSymbol,
                             std::string issuedDate, std::string dueDate, std::vector<InvoiceItem> items) {
    auto supplier = database.getSubject(supplierId);
    auto customer = database.getSubject(customerId);
    assert(database.addInvoice(Invoice(++counter, *supplier, *customer, variableSymbol, constantSymbol, issuedDate, dueDate, items)));
    return counter;
}

std::string InvoiceFacade::getInvoiceSupplierName(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_supplier.getName();
}

std::string InvoiceFacade::getInvoiceSupplierRegistrationId(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_supplier.getRegistrationId();
}

std::string InvoiceFacade::getInvoiceSupplierVatId(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_supplier.getVatId();
}

std::string InvoiceFacade::getInvoiceSupplierAddress(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_supplier.getAddress();
}

std::string InvoiceFacade::getInvoiceSupplierBankAccount(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_supplier.getbankAccount();
}

std::string InvoiceFacade::getInvoiceCustomerName(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_buyer.getName();
}

std::string InvoiceFacade::getInvoiceCustomerRegistrationId(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_buyer.getRegistrationId();
}

std::string InvoiceFacade::getInvoiceCustomerVatId(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_buyer.getVatId();
}

std::string InvoiceFacade::getInvoiceCustomerAddress(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_buyer.getAddress();
}

unsigned int InvoiceFacade::getInvoiceVariableSymbol(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return 0;
    return invoiceFound->m_variableCode;
}

unsigned int InvoiceFacade::getInvoiceConstantSymbol(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return 0;
    return invoiceFound->m_constantCode;
}

std::string InvoiceFacade::getInvoiceIssuedDate(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_invoiceDate;
}

std::string InvoiceFacade::getInvoiceDueDate(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return "";
    return invoiceFound->m_dueDate;
}

unsigned int InvoiceFacade::getInvoiceSubtotal(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return UINT32_MAX;

    unsigned int subtotal = 0;
    for (InvoiceItem item : invoiceFound->m_items) {
        subtotal += item.getAmount();
    }
    return subtotal;
}

unsigned int InvoiceFacade::getInvoiceTax(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return UINT32_MAX;

    unsigned int tax = 0;
    for (InvoiceItem item : invoiceFound->m_items) {
        tax += (item.getAmount() * item.getTaxRate()) / 100;
    }
    return tax;
}

unsigned int InvoiceFacade::getInvoiceTotal(unsigned invoiceId) const {
    auto invoiceFound = database.getInvoice(invoiceId);
    if (invoiceFound == nullptr) return UINT32_MAX;

    unsigned int total = 0;
    for (InvoiceItem item : invoiceFound->m_items) {
        total += item.getAmount() + (item.getAmount() * item.getTaxRate()) / 100;
    }
    return total;
}

unsigned int InvoiceFacade::getTotalInvoicedToCustomer(unsigned customerId) const {
    if (!database.getSubject(customerId)) return UINT32_MAX; //customer not found

    unsigned int total = 0;
    for (auto invoice : database.getInvoicesByCustomer(customerId)) {
        for (auto item : invoice->m_items) {
            total += item.getAmount() + ((item.getAmount() * item.getTaxRate()) / 100);
        }
    }
    return total;
}

unsigned int InvoiceFacade::getTotalInvoicedFromSupplier(unsigned supplierId) const {
    if (!database.getSubject(supplierId)) return UINT32_MAX; //customer not found

    unsigned int total = 0;
    for (auto invoice : database.getInvoicesBySupplier(supplierId)) {
        for (auto item : invoice->m_items) {
            total += item.getAmount() + ((item.getAmount() * item.getTaxRate()) / 100);
        }
    }
    return total;
}

const std::vector<InvoiceItem> &InvoiceFacade::getItems(unsigned invoiceId) const {
    return database.getInvoice(invoiceId)->m_items;
}
