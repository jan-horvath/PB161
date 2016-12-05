#include "../ServiceContainer.hpp"
#include <gtest/gtest.h>

TEST(ServiceContainer, functional) {
	ServiceContainer dic;
	InvoiceFacadeInterface &invoiceFacade = dic.getInvoiceFacade();
	SubjectsFacadeInterface &subjectsFacade = dic.getSubjectsFacade();

	unsigned filipId = subjectsFacade.createSubject("Filip Prochazka", "01310534", "CZ9104154433", "Brno", "1109451029/3030");
	unsigned muniId = subjectsFacade.createSubject("Masarykova Univerzita", "00216224", "CZ00216224", "Brno", "");

	unsigned invoice = invoiceFacade.createInvoice(
	    filipId,
	    muniId,
	    123,
	    123,
	    "13.08.2016",
	    "13.09.2016",
	    {
	        InvoiceItem("Priprava domaciho ukolu C++", 100, 21),
	        InvoiceItem("Rady studentum na foru", 200, 15),
	    });

	ASSERT_EQ(300, invoiceFacade.getInvoiceSubtotal(invoice));
	ASSERT_EQ(51, invoiceFacade.getInvoiceTax(invoice));
	ASSERT_EQ(351, invoiceFacade.getInvoiceTotal(invoice));
}
