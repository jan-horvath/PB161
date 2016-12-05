#ifndef HW03_ACCOUNTING_SERVICE_CONTAINER_H
#define HW03_ACCOUNTING_SERVICE_CONTAINER_H

#include "InvoiceFacade.hpp"
#include "ServiceContainerInterface.hpp"
#include "SubjectsFacadeInterface.hpp"
#include "Database.hpp"
#include "SubjectFacade.hpp"
#include <memory>

/**
 * You can modify this class however you like, as long as implement the ServiceContainerInterface and keep the default constructor.
 *
 * The point of this class is to allow you to have dependencies between services and facades.
 * Kontr will simply fetch the ready-made objects from this container and don't have to care about the implementation details.
 */
class ServiceContainer : public ServiceContainerInterface {
	std::unique_ptr<InvoiceFacade> invoiceFacade;
    std::unique_ptr<SubjectFacade> subjectFacade;
    Database database;

public:
	ServiceContainer() {
		invoiceFacade = std::make_unique<InvoiceFacade>(database);
        subjectFacade = std::make_unique<SubjectFacade>(database);
	}

	InvoiceFacadeInterface &getInvoiceFacade() override {
		return *invoiceFacade;
	}

    virtual SubjectsFacadeInterface &getSubjectsFacade() override {
        return *subjectFacade;
    }
};

#endif //HW03_ACCOUNTING_SERVICE_CONTAINER_H
