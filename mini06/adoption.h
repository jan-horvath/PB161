//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ADOPTION_H
#define HW01_ADOPTION_H

#include "animal.h"
#include "person.h"
#include <ostream>

class Adoption {
public:
  const Person adopter;
  const Animal animal;
  const unsigned int amount;

  Adoption(const Person &adopter, const Animal &animal,
           const unsigned int amount)
      : adopter(adopter), animal(animal), amount(amount) {}

  bool operator==(const Adoption &rhs) const {
    return ((adopter == rhs.adopter) && (animal == rhs.animal));
  }

  bool operator!=(const Adoption &rhs) const { return !(rhs == *this); }

  friend std::ostream &operator<<(std::ostream &os, const Adoption &adoption) {
    os << adoption.adopter << adoption.animal << "Amount: " << adoption.amount
       << std::endl;
    return os;
  }
};

#endif // HW01_ADOPTION_H
