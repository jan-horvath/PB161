//
// Created by Jan Horvath on 03-Dec-16.
//
#include <iostream>
#include "ServiceContainerInterface.hpp"
#include "SubjectFacade.hpp"
#include "InvoiceFacade.hpp"
#include "ServiceContainer.hpp"

using namespace std;

void DisplayHelp() {
  cout << "* help - outputs this help" << endl;
  cout << "* quit" << endl;
  cout << "* createSubject" << endl;
  cout << "* updateSubject <id>" << endl;
  cout << "* printSubject <id>" << endl;
  cout << "* createInvoice" << endl;
  cout << "* printInvoice <id>" << endl;
}

void CreateSubject(SubjectsFacadeInterface& subjectFacade) {
  string name, regId, vatId, address, bankAcc;
  cout << "subject name: ";
  getline(cin, name);
  cout << "registration id: ";
  getline(cin, regId);
  cout << "vat id: ";
  getline(cin, vatId);
  cout << "address: ";
  getline(cin, address);
  cout << "bank account: ";
  getline(cin, bankAcc);

  unsigned id;
  id = subjectFacade.createSubject(name, regId, vatId, address, bankAcc);
  cout << "subject created: " << id << endl;
}

bool UpdateSubject(unsigned id, SubjectsFacadeInterface& subjectFacade) {
  if (subjectFacade.getSubjectName(id).empty())
    return false;
  string name, regId, vatId, address, bankAcc;
  cout << "subject name: ";
  getline(cin, name);
  cout << "registration id: ";
  getline(cin, regId);
  cout << "vat id: ";
  getline(cin, vatId);
  cout << "address: ";
  getline(cin, address);
  cout << "bank account: ";
  getline(cin, bankAcc);

  subjectFacade.updateSubject(id, name, regId, vatId, address, bankAcc);
  return true;
}

bool PrintSubject(unsigned id, SubjectsFacadeInterface& subjectFacade) {
  if (subjectFacade.getSubjectName(id).empty()) {
    return false;
  }
  cout << "subject name: " << subjectFacade.getSubjectName(id) << endl;
  cout << "registration id: " << subjectFacade.getSubjectRegistrationId(id)
       << endl;
  cout << "vat id: " << subjectFacade.getSubjectVatId(id) << endl;
  cout << "address: " << subjectFacade.getSubjectAddress(id) << endl;
  cout << "bank account: " << subjectFacade.getSubjectBankAccount(id) << endl;
  return true;
}

unsigned CreateItems(vector<InvoiceItem>& items, unsigned count) {
  string itemName, toBeConverted;
  unsigned itemAmount, itemTaxRate;
  for (unsigned i = 1; i <= count; ++i) {
    cout << "item " << i << " title: ";
    getline(cin, itemName);

    cout << "item " << i << " amount: ";
    getline(cin, toBeConverted);
    try {
      itemAmount = stoi(toBeConverted);
    } catch (invalid_argument&) {
      return 3;
    }

    cout << "item " << i << " tax rate: ";
    getline(cin, toBeConverted);
    try {
      itemTaxRate = stoi(toBeConverted);
    } catch (invalid_argument&) {
      return 3;
    }
    if (itemTaxRate > 100) {
      return 4;
    }

    items.push_back(InvoiceItem(itemName, itemAmount, itemTaxRate));
  }
  return 0;
}

unsigned CreateInvoice(InvoiceFacadeInterface& invoiceFacade,
                       SubjectsFacadeInterface& subjectFacade) {
  unsigned supplierId, customerId, varSymbol, constSymbol, numOfItems;
  string issuedDate, dueDate, toBeConverted;
  vector<InvoiceItem> items;

  cout << "supplier id: ";
  getline(cin, toBeConverted);
  supplierId = stoi(toBeConverted);
  if (!subjectFacade.containsSubject(supplierId))
    return 1;

  cout << "customer id: ";
  getline(cin, toBeConverted);
  customerId = stoi(toBeConverted);
  if (!subjectFacade.containsSubject(customerId))
    return 2;

  cout << "variable symbol: ";
  getline(cin, toBeConverted);
  try {
    varSymbol = stoi(toBeConverted);
  } catch (invalid_argument&) {
    return 3;
  }

  cout << "constant symbol: ";
  getline(cin, toBeConverted);
  try {
    constSymbol = stoi(toBeConverted);
  } catch (invalid_argument&) {
    return 3;
  }

  cout << "issued date: ";
  getline(cin, issuedDate);

  cout << "due date: ";
  getline(cin, dueDate);

  cout << "add items: ";
  getline(cin, toBeConverted);
  try {
    numOfItems = stoi(toBeConverted);
  } catch (invalid_argument&) {
    return 3;
  }

  unsigned error = CreateItems(items, numOfItems);
  if (error != 0)
    return error;

  unsigned id =
      invoiceFacade.createInvoice(supplierId, customerId, varSymbol,
                                  constSymbol, issuedDate, dueDate, items);
  cout << "invoice created: " << id << endl;
  return 0;
}

bool PrintInvoice(unsigned id, InvoiceFacadeInterface& invoiceFacade) {
  if (invoiceFacade.getInvoiceCustomerName(id).empty())
    return false;
  cout << "# Customer" << endl;
  cout << "subject name: " << invoiceFacade.getInvoiceCustomerName(id) << endl;
  cout << "registration id: "
       << invoiceFacade.getInvoiceCustomerRegistrationId(id) << endl;
  cout << "vat id: " << invoiceFacade.getInvoiceCustomerVatId(id) << endl;
  cout << "address: " << invoiceFacade.getInvoiceCustomerAddress(id) << endl
       << endl;
  cout << "# Supplier" << endl;
  cout << "subject name: " << invoiceFacade.getInvoiceSupplierName(id) << endl;
  cout << "registration id: "
       << invoiceFacade.getInvoiceSupplierRegistrationId(id) << endl;
  cout << "vat id: " << invoiceFacade.getInvoiceSupplierVatId(id) << endl;
  cout << "address: " << invoiceFacade.getInvoiceSupplierAddress(id) << endl;
  cout << "bank account: " << invoiceFacade.getInvoiceSupplierBankAccount(id)
       << endl
       << endl;
  for (InvoiceItem item : invoiceFacade.getItems(id)) {
    cout << "* " << item.getTitle() << ", " << item.getAmount() << ", "
         << item.getTaxRate() << "%" << endl;
  }
  cout << "Tax: " << invoiceFacade.getInvoiceTax(id) << endl;
  cout << "Subtotal: " << invoiceFacade.getInvoiceSubtotal(id) << endl;
  cout << "Total: " << invoiceFacade.getInvoiceTotal(id) << endl;
  return true;
}

void init() {
  ServiceContainer container;
  InvoiceFacadeInterface& invoiceFacade = container.getInvoiceFacade();
  SubjectsFacadeInterface& subjectFacade = container.getSubjectsFacade();

  string choice = "help";
  bool unknownCommand = true;
  while (choice != "quit") {
    if (choice == "help") {
      unknownCommand = false;
      DisplayHelp();
    }
    if (choice == "createSubject") {
      unknownCommand = false;
      CreateSubject(subjectFacade);
    }
    if (choice.compare(0, 14, "updateSubject ") == 0) {
      unknownCommand = false;
      unsigned id = stoi(choice.substr(14));
      if (!UpdateSubject(id, subjectFacade)) {
        cerr << "subject not found" << endl;
      } else {
        cout << "subject updated" << endl;
      }
    }
    if (choice.compare(0, 13, "printSubject ") == 0) {
      unknownCommand = false;
      unsigned id = stoi(choice.substr(13));
      if (!PrintSubject(id, subjectFacade)) {
        cerr << "subject not found" << endl;
      }
    }
    if (choice == "createInvoice") {
      unknownCommand = false;
      unsigned error = CreateInvoice(invoiceFacade, subjectFacade);
      if (error == 1)
        cerr << "supplier not found" << endl;
      if (error == 2)
        cerr << "customer not found" << endl;
      if (error == 3)
        cerr << "not a number" << endl;
      if (error == 4)
        cerr << "invalid tax rate" << endl;
    }
    if (choice.compare(0, 13, "printInvoice ") == 0) {
      unknownCommand = false;
      unsigned id = stoi(choice.substr(13));
      if (!PrintInvoice(id, invoiceFacade)) {
        cerr << "invoice not found" << endl;
      }
    }
    if (unknownCommand) {
      cerr << "unknown command " << choice << endl;
    }
    cout << "> ";
    getline(cin, choice);
    unknownCommand = true;
  }
}
