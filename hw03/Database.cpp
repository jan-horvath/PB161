//
// Created by Jan Horvath on 03-Dec-16.
//

#include "Database.hpp"

bool Database::containsInvoice(unsigned id) {
    for (const std::unique_ptr<Invoice> &inv : m_invoices) {
        if (inv->m_Id == id) return true;
    }
    return false;
}

bool Database::containsSubject(unsigned id) {
    for (const std::unique_ptr<Subject> &subj : m_subjects) {
        if (subj->getId() == id) return true;
    }
    return false;
}

bool Database::addInvoice(const Invoice &invoice) {
    if (!containsInvoice(invoice.m_Id)) {
        m_invoices.push_back(std::make_unique<Invoice>(invoice));
        return true;
    }
    return false;
}

Invoice const *Database::getInvoice(unsigned id) const {
    for (const std::unique_ptr<Invoice> &invoice : m_invoices) {
        if (invoice->m_Id == id) return invoice.get();
    }
    return nullptr;
}

bool Database::addSubject(const Subject &subject) {
    if (!containsSubject(subject.getId())) {
        m_subjects.push_back(std::make_unique<Subject>(subject));
        return true;
    }
    return false;
}

Subject const *Database::getSubject(unsigned id) const {
    for (const std::unique_ptr<Subject> &subject : m_subjects) {
        if (subject->getId() == id) return subject.get();
    }
    return nullptr;
}

bool Database::updateSubject(const Subject &subject) {
    for (std::unique_ptr<Subject> &subjectFound: m_subjects) {
        if (subjectFound->getId() == subject.getId()) {
            subjectFound->setAccount(subject.getbankAccount());
            subjectFound->setAddress(subject.getAddress());
            subjectFound->setName(subject.getName());
            subjectFound->setRegistrationId(subject.getRegistrationId());
            subjectFound->setVatId(subject.getVatId());
            return true;
        }
    }
    return false;
}

std::vector<Invoice const*> Database::getInvoicesByCustomer(unsigned int customerId) {
    std::vector<Invoice const*> invoicesByCustomer;
    for (const std::unique_ptr<Invoice> &invoice : m_invoices) {
        if (invoice->m_buyer.getId() == customerId) invoicesByCustomer.push_back(invoice.get());
    }
    return invoicesByCustomer;
}

std::vector<Invoice const*> Database::getInvoicesBySupplier(unsigned int supplierId) {
    std::vector<Invoice const*> invoicesBySupplier;
    for (const std::unique_ptr<Invoice> &invoice: m_invoices) {
        if (invoice->m_supplier.getId() == supplierId) invoicesBySupplier.push_back(invoice.get());
    }
    return invoicesBySupplier;
}
