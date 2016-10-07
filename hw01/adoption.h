//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ADOPTION_H
#define HW01_ADOPTION_H

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

	void print() const {
		adopter.print();
		animal.print();
		std::cout << "Amount: " << amount << std::endl;
	}
};

#endif //HW01_ADOPTION_H
