//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_PERSON_H
#define HW01_PERSON_H

#include <iostream>
#include <string>

class Person {

public:
	const std::string name;
	const std::string email; //ID
	const std::string city;

	Person(const std::string name, const std::string email, const std::string city) : name(name), email(email),
	                                                                                  city(city) {}
	bool operator==(const std::string &rhs) const {
		return email==rhs;
	}

	bool operator!=(const std::string &rhs) const {
		return !(*this==rhs);
	}

	bool operator==(const Person &rhs) const {
		return email==rhs.email;
	}

	bool operator!=(const Person &rhs) const {
		return !(rhs == *this);
	}

	/*
	bool equalTo(const Person &person) const {
		return this->equalId(person.email);
	}
	 */

	bool hasCity() const {
		return city != "";
	}

	friend std::ostream &operator<<(std::ostream &os, const Person &person) {
		os << person.name + " <" + person.email + ">";
		if (person.hasCity()) {
			os << ", " << person.city;
		}
		os << std::endl;
		return os;
	}

	/*
	void print() const {
		std::cout << name + " <" + email + ">";
		if (hasCity())
			std::cout << ", " << city;
		std::cout << std::endl;
	}*/
};

inline bool operator==(const std::string &lhs, const Person &rhs) {
	return lhs==rhs.email;
}

inline bool operator!=(const std::string &lhs, const Person &rhs) {
	return !(lhs == rhs);
}


#endif //HW01_PERSON_H
