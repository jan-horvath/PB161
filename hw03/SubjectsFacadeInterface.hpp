#ifndef HW03_ACCOUNTING_FACADE_INTERFACE_H
#define HW03_ACCOUNTING_FACADE_INTERFACE_H

#include <string>
#include <vector>

/**
 * You can add new methods, but do not remove or modify the existing ones.
 */
class SubjectsFacadeInterface {
 public:
  virtual ~SubjectsFacadeInterface() = default;

  virtual unsigned createSubject(std::string name,
                                 std::string registrationId,
                                 std::string vatId,
                                 std::string address,
                                 std::string bankAccount) = 0;

  virtual void updateSubject(unsigned subjectId,
                             std::string name,
                             std::string registrationId,
                             std::string vatId,
                             std::string address,
                             std::string bankAccount) = 0;

  virtual std::string getSubjectName(unsigned subjectId) const = 0;
  virtual std::string getSubjectRegistrationId(unsigned subjectId) const = 0;
  virtual std::string getSubjectVatId(unsigned subjectId) const = 0;
  virtual std::string getSubjectAddress(unsigned subjectId) const = 0;
  virtual std::string getSubjectBankAccount(unsigned subjectId) const = 0;
  virtual bool containsSubject(unsigned id) const = 0;
  virtual bool isUpdateSuccessful() const = 0;
};

#endif  // HW03_ACCOUNTING_FACADE_INTERFACE_H
