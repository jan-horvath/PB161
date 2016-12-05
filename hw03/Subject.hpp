//
// Created by Jan Horvath on 03-Dec-16.
//

#ifndef HW03_ACCOUNTING_SUBJECT_HPP
#define HW03_ACCOUNTING_SUBJECT_HPP

#include <string>

class Subject {
private:
    const unsigned int m_Id;
    std::string m_name;
    std::string m_registrationId;
    std::string m_vatId;
    std::string m_address;
    std::string m_bankAccount;

public:
    Subject(unsigned id, const std::string &m_name, const std::string &m_registrationId, const std::string &m_vatId,
            const std::string &m_address, const std::string &m_account) : m_Id(id), m_name(m_name),
                                                                          m_registrationId(m_registrationId),
                                                                          m_vatId(m_vatId), m_address(m_address),
                                                                          m_bankAccount(m_account) {}

    unsigned int getId() const {
        return m_Id;
    }

    const std::string &getName() const {
        return m_name;
    }

    void setName(const std::string &m_name) {
        Subject::m_name = m_name;
    }

    const std::string &getRegistrationId() const {
        return m_registrationId;
    }

    void setRegistrationId(const std::string &m_registrationId) {
        Subject::m_registrationId = m_registrationId;
    }

    const std::string &getVatId() const {
        return m_vatId;
    }

    void setVatId(const std::string &m_vatId) {
        Subject::m_vatId = m_vatId;
    }

    const std::string &getAddress() const {
        return m_address;
    }

    void setAddress(const std::string &m_address) {
        Subject::m_address = m_address;
    }

    const std::string &getbankAccount() const {
        return m_bankAccount;
    }

    void setAccount(const std::string &m_account) {
        Subject::m_bankAccount = m_account;
    }
};

#endif //HW03_ACCOUNTING_SUBJECT_HPP
