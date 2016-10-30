//
// Created by Jan Horvath on 06-Oct-16.
//

#include "zoo.h"
#include <cassert>


bool Zoo::addPerson(const Person &person) {
	for (const Person &adopter : adopters) {
		if (person==adopter)
			return false;
	}
	adopters.push_back(person);
	return true;
}

bool Zoo::addAnimal(const Animal &animal) {
	for (const Animal &zooAnimal : animals) {
		if (zooAnimal==animal)
			return false;
	}
	animals.push_back(animal);
	return true;
}

bool Zoo::hasPerson(const std::string &email) const {
	for (const Person &adopter : adopters) {
		if (adopter.equalId(email))
			return true;
	}
	return false;
}

bool Zoo::hasAnimal(const std::string &name) const {
	for (const Animal &animal : animals) {
		if (animal.equalId(name))
			return true;
	}
	return false;
}

const Person &Zoo::findPerson(const std::string &email) const {
	for (const Person &adopter : adopters) {
		if (adopter.equalId(email))
			return adopter;
	}
	assert(false);
}

const Animal &Zoo::findAnimal(const std::string &name) const {
	for (const Animal &animal : animals) {
		if (animal.equalId(name))
			return animal;
	}
	assert(false);
}

bool Zoo::adopt(const Adoption &adoption) {
	for (const Adoption &existingAdoption : adoptions) {
		if (adoption==existingAdoption)
			return false;
	}
	adoptions.push_back(adoption);
	return true;
}

const std::vector<Person> &Zoo::getPeople() const {
	return adopters;
}

const std::vector<Animal> &Zoo::getAnimals() const {
	return animals;
}

const std::vector<Adoption> &Zoo::getAdoptions() const {
	return adoptions;
}

std::vector<Person> Zoo::getAdoptersForPlaque(const Animal &animal) const {
	std::vector<Person> adoptersForPlaque;

	for (const Adoption &adoption : adoptions) {
		if (adoption.animal==animal)
			adoptersForPlaque.push_back(adoption.adopter);
	}
	return adoptersForPlaque;
}
