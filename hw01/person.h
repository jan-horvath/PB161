//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_PERSON_H
#define HW01_PERSON_H

#include <string>
#include <iostream>

class Person {

public:
    const std::string name;
    const std::string email; //ID
    const std::string city;

    Person(std::string name, std::string email, std::string city) : name(name), email(email), city(city) {}

    bool equalId(std::string email) const {
        return email == this->email;
    }

    bool equalTo(Person person) const {
        return this->equalId(person.email);
    }

    bool hasCity() const {
        return city != "";
    }

    void print() const {
        std::cout << this->name + " <" + this->email + ">";
        if (hasCity()) std::cout << ", " << this->city;
        std::cout << std::endl;
    }

};


#endif //HW01_PERSON_H
