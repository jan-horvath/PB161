#ifndef HW03_ACCOUNTING_INVOICE_FACADE_H
#define HW03_ACCOUNTING_INVOICE_FACADE_H

#include "InvoiceFacadeInterface.hpp"
#include "Database.hpp"

class InvoiceFacade : public InvoiceFacadeInterface {
private:
    Database &database;
    unsigned int counter;
public:
    InvoiceFacade(Database &database) : database(database) {}

    virtual unsigned int
    createInvoice(unsigned supplierId, unsigned customerId, unsigned variableSymbol, unsigned constantSymbol,
                  std::string issuedDate, std::string dueDate, std::vector<InvoiceItem> items) override;

    virtual std::string getInvoiceSupplierName(unsigned invoiceId) const override;

    virtual std::string getInvoiceSupplierRegistrationId(unsigned invoiceId) const override;

    virtual std::string getInvoiceSupplierVatId(unsigned invoiceId) const override;

    virtual std::string getInvoiceSupplierAddress(unsigned invoiceId) const override;

    virtual std::string getInvoiceSupplierBankAccount(unsigned invoiceId) const override;

    virtual std::string getInvoiceCustomerName(unsigned invoiceId) const override;

    virtual std::string getInvoiceCustomerRegistrationId(unsigned invoiceId) const override;

    virtual std::string getInvoiceCustomerVatId(unsigned invoiceId) const override;

    virtual std::string getInvoiceCustomerAddress(unsigned invoiceId) const override;

    virtual unsigned int getInvoiceVariableSymbol(unsigned invoiceId) const override;

    virtual unsigned int getInvoiceConstantSymbol(unsigned invoiceId) const override;

    virtual std::string getInvoiceIssuedDate(unsigned invoiceId) const override;

    virtual std::string getInvoiceDueDate(unsigned invoiceId) const override;

    virtual unsigned int getInvoiceSubtotal(unsigned invoiceId) const override;

    virtual unsigned int getInvoiceTax(unsigned invoiceId) const override;

    virtual unsigned int getInvoiceTotal(unsigned invoiceId) const override;

    virtual unsigned int getTotalInvoicedToCustomer(unsigned customerId) const override;

    virtual unsigned int getTotalInvoicedFromSupplier(unsigned supplierId) const override;

    virtual const std::vector<InvoiceItem> &getItems(unsigned invoiceId) const override;
};

#endif //HW03_ACCOUNTING_INVOICE_FACADE_H
