//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ANIMAL_H
#define HW01_ANIMAL_H

#include <iostream>
#include <string>

class Animal {
public:
  const std::string name; // ID
  const std::string description;

  Animal(const std::string &name, const std::string &description)
      : name(name), description(description) {}

  bool operator==(const std::string &rhs) const { return name == rhs; }

  bool operator!=(const std::string &rhs) const { return !(*this == rhs); }

  bool operator==(const Animal &rhs) const { return rhs.name == name; }

  bool operator!=(const Animal &rhs) const { return !(rhs == *this); }

  bool hasDescription() const { return !description.empty(); }

  friend std::ostream &operator<<(std::ostream &os, const Animal &animal) {
    os << animal.name << std::endl;
    if (animal.hasDescription()) {
      os << animal.description << std::endl;
    }
    return os;
  }
};

inline bool operator==(const std::string &lhs, const Animal &rhs) {
  return lhs == rhs.name;
}

inline bool operator!=(const std::string &lhs, const Animal &rhs) {
  return !(lhs == rhs);
}

#endif // HW01_ANIMAL_H
