//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ADOPTION_H
#define HW01_ADOPTION_H

#include <ostream>
#include "animal.h"
#include "person.h"

class Adoption {
public:
	const Person adopter;
	const Animal animal;
	const unsigned int amount;

	Adoption(const Person &adopter, const Animal &animal, const unsigned int amount) : adopter(adopter), animal(animal),
	                                                                                   amount(amount) {}

	bool equalTo(const Adoption &adoption) const {
		return ((this->adopter.equalTo(adoption.adopter))
		    && (this->animal.equalTo(adoption.animal)));
	}

	friend std::ostream &operator<<(std::ostream &os, const Adoption &adoption) {
		os << adoption.adopter << adoption.animal << "Amount: "
		   << adoption.amount << std::endl;
		return os;
	}

	/*
	void print() const {
		std::cout << adopter;
		std::cout << animal;
		std::cout << "Amount: " << amount << std::endl;
	}
	 */
};

#endif //HW01_ADOPTION_H
