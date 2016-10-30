//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ANIMAL_H
#define HW01_ANIMAL_H

#include <iostream>
#include <string>

class Animal {
public:
	const std::string name; //ID
	const std::string description;

	Animal(const std::string name, const std::string description) : name(name), description(description) {}

	bool equalId(const std::string &name) const {
		return this->name == name;
	}

	bool operator==(const Animal &rhs) const {
		return name == rhs.name;
	}

	bool operator!=(const Animal &rhs) const {
		return !(rhs == *this);
	}

	/*
	bool equalTo(const Animal &animal) const {
		return (this->equalId(animal.name));
	}
	 */

	bool hasDescription() const {
		return description != "";
	}

	friend std::ostream &operator<<(std::ostream &os, const Animal &animal) {
		os << animal.name << std::endl;
		if (animal.hasDescription()) {
			os << animal.description << std::endl;
		}
		return os;
	}

	/*
	void print() const {
		std::cout << name << std::endl;
		if (hasDescription())
			std::cout << description << std::endl;
	}
	 */
};


#endif //HW01_ANIMAL_H
