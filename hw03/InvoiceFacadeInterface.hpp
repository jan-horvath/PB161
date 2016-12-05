#ifndef HW03_ACCOUNTING_INVOICE_FACADE_INTERFACE_H
#define HW03_ACCOUNTING_INVOICE_FACADE_INTERFACE_H

#include <string>
#include <vector>

#include "InvoiceItem.hpp"

/**
 * You can add new methods, but do not remove or modify the existing ones.
 */
class InvoiceFacadeInterface {
public:
	virtual ~InvoiceFacadeInterface() = default;

	virtual unsigned createInvoice(
	    unsigned supplierId,
	    unsigned customerId,
	    unsigned variableSymbol,
	    unsigned constantSymbol,
	    std::string issuedDate,
	    std::string dueDate,
	    std::vector<InvoiceItem> items)
	    = 0;

	virtual std::string getInvoiceSupplierName(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceSupplierRegistrationId(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceSupplierVatId(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceSupplierAddress(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceSupplierBankAccount(unsigned invoiceId) const = 0;

	virtual std::string getInvoiceCustomerName(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceCustomerRegistrationId(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceCustomerVatId(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceCustomerAddress(unsigned invoiceId) const = 0;

	virtual unsigned getInvoiceVariableSymbol(unsigned invoiceId) const = 0;
	virtual unsigned getInvoiceConstantSymbol(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceIssuedDate(unsigned invoiceId) const = 0;
	virtual std::string getInvoiceDueDate(unsigned invoiceId) const = 0;
	virtual const std::vector<InvoiceItem> &getItems(unsigned invoiceId) const = 0;

	virtual unsigned getInvoiceSubtotal(unsigned invoiceId) const = 0;
	virtual unsigned getInvoiceTax(unsigned invoiceId) const = 0;
	virtual unsigned getInvoiceTotal(unsigned invoiceId) const = 0;

	// aggregate functions working over all invoices
	virtual unsigned getTotalInvoicedToCustomer(unsigned customerId) const = 0;
	virtual unsigned getTotalInvoicedFromSupplier(unsigned supplierId) const = 0;
};

#endif //HW03_ACCOUNTING_INVOICEFACADE_H
