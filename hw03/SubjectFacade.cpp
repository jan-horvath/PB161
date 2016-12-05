//
// Created by Jan Horvath on 03-Dec-16.
//

#include <string>
#include <cassert>
#include "SubjectFacade.hpp"

unsigned int
SubjectFacade::createSubject(std::string name, std::string registrationId, std::string vatId, std::string address,
                             std::string bankAccount) {
    assert(database.addSubject(Subject(++counter, name, registrationId, vatId, address, bankAccount)));
    return counter;
}

void SubjectFacade::updateSubject(unsigned subjectId, std::string name, std::string registrationId, std::string vatId,
                                  std::string address, std::string bankAccount) {
    updateSuccessful = false;
    updateSuccessful = database.updateSubject(Subject(subjectId, name, registrationId, vatId, address, bankAccount));
}

std::string SubjectFacade::getSubjectName(unsigned subjectId) const {
    auto subjectFound = database.getSubject(subjectId);
    if (subjectFound == nullptr) {
        return "";
    }
    return subjectFound->getName();

}

std::string SubjectFacade::getSubjectRegistrationId(unsigned subjectId) const {
    auto subjectFound = database.getSubject(subjectId);
    if (subjectFound == nullptr) {
        return 0;
    }
    return subjectFound->getRegistrationId();
}

std::string SubjectFacade::getSubjectVatId(unsigned subjectId) const {
    auto subjectFound = database.getSubject(subjectId);
    if (subjectFound == nullptr) {
        return "";
    }
    return subjectFound->getVatId();
}

std::string SubjectFacade::getSubjectAddress(unsigned subjectId) const {
    auto subjectFound = database.getSubject(subjectId);
    if (subjectFound == nullptr) {
        return "";
    }
    return subjectFound->getAddress();
}

std::string SubjectFacade::getSubjectBankAccount(unsigned subjectId) const {
    auto subjectFound = database.getSubject(subjectId);
    if (subjectFound == nullptr) {
        return "";
    }
    return subjectFound->getbankAccount();
}

bool SubjectFacade::isUpdateSuccessful() const {
    return updateSuccessful;
}

bool SubjectFacade::containsSubject(unsigned id) const {
    return database.containsSubject(id);
}

