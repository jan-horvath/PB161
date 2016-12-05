//
// Created by Jan Horvath on 03-Dec-16.
//

#ifndef HW03_ACCOUNTING_SUBJECTFACADE_HPP
#define HW03_ACCOUNTING_SUBJECTFACADE_HPP

#include "SubjectsFacadeInterface.hpp"
#include "Database.hpp"

class SubjectFacade : public SubjectsFacadeInterface {
private:
    Database &database;
    unsigned int counter;
    bool updateSuccessful;
public:
    virtual ~SubjectFacade() override = default;

    SubjectFacade(Database &database) : database(database), counter(0), updateSuccessful(false) {}

    virtual unsigned int
    createSubject(std::string name, std::string registrationId, std::string vatId, std::string address,
                  std::string bankAccount) override;

    virtual void updateSubject(unsigned subjectId, std::string name, std::string registrationId, std::string vatId,
                               std::string address, std::string bankAccount) override;

    virtual std::string getSubjectName(unsigned subjectId) const override;

    virtual std::string getSubjectRegistrationId(unsigned subjectId) const override;

    virtual std::string getSubjectVatId(unsigned subjectId) const override;

    virtual std::string getSubjectAddress(unsigned subjectId) const override;

    virtual std::string getSubjectBankAccount(unsigned subjectId) const override;

    virtual bool isUpdateSuccessful() const override;

    virtual bool containsSubject(unsigned id) const override;
};

#endif //HW03_ACCOUNTING_SUBJECTFACADE_HPP
