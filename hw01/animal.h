//
// Created by Jan Horvath on 06-Oct-16.
//

#ifndef HW01_ANIMAL_H
#define HW01_ANIMAL_H

#include <string>
#include <iostream>

class Animal {
public:
    const std::string name; //ID
    const std::string description;

    Animal(std::string name, std::string description) : name(name), description(description) {}

    bool equalId(std::string name) const {
        return this->name == name;
    }

    bool equalTo(Animal animal) const {
        return (this->equalId(animal.name));
    }

    bool hasDescription() const {
        return description != "";
    }

    void print() const {
        std::cout << name << std::endl;
        if (hasDescription()) std::cout << description << std::endl;
    }
};


#endif //HW01_ANIMAL_H
