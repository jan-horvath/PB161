//
// Created by Jan Horvath on 06-Oct-16.
//

#include <iostream>
#include "handler.h"
#include "zoo.h"

void Handler::handle() {
    using namespace std;
    Zoo zoo;

    char choice = '9';
    string input;

    while (choice != '0') {
        cout << "Actions:" << endl;
        cout << "       0 -> exit program" << endl;
        cout << "       1 -> add person" << endl;
        cout << "       2 -> add animal" << endl;
        cout << "       3 -> adopt" << endl;
        cout << "       4 -> print people" << endl;
        cout << "       5 -> print animals" << endl;
        cout << "       6 -> print adoptions" << endl;
        cout << "       7 -> get adopters for plaque" << endl;

        getline(cin, input);
        if (input.length() != 1) {
            choice = '8';
        } else {
            choice = input[0];
        }

        switch (choice) {
            case '0':
                break;
            case '1': {
                string name;
                string email;
                string city;

                cout << "Name:" << endl;
                getline(cin, name);
                if (name == "") {
                    cerr << "Name cannot be blank!";
                    break;
                }

                cout << "Email:" << endl;
                getline(cin, email);
                if (email == "") {
                    cerr << "Email cannot be blank!";
                    break;
                }

                cout << "City:" << endl;
                getline(cin, city);

                if (zoo.hasPerson(email)) {
                    cerr << "Person already exists in database." << endl;
                    break;
                }
                zoo.addPerson(Person(name, email, city));
                cout << "OK" << endl;
                break;
            }
            case '2': {
                string name;

                string description;
                cout << "Name:" << endl;
                getline(cin, name);
                if (name == "") {
                    cerr << "Name cannot be blank!";
                    break;
                }

                cout << "Description:" << endl;
                getline(cin, description);


                if (zoo.hasAnimal(name)) {
                    cerr << "Animal already exists in database." << endl;
                    break;
                }
                zoo.addAnimal(Animal(name, description));
                cout << "OK" << endl;
                break;
            }
            case '3': {
                string email;
                string name;
                string amountString;
                unsigned int amount;

                cout << "Existing person's email:" << endl;
                getline(cin, email);
                if (email == "") {
                    cerr << "Email cannot be blank!";
                    break;
                }
                if (!zoo.hasPerson(email)) {
                    cerr << "Person does not exist!" << endl;
                }

                cout << "Animal's name:" << endl;
                getline(cin, name);
                if (name == "") {
                    cerr << "Animal's name cannot be blank!";
                    break;
                }
                if (!zoo.hasAnimal(name)) {
                    cerr << "Animal does not exist!" << endl;
                    break;
                }

                cout << "Amount donated:" << endl;
                getline(cin, amountString);
                amount = stoi(amountString);

                Person person = zoo.findPerson(email);
                Animal animal = zoo.findAnimal(name);
                if (zoo.adopt(Adoption(person, animal, amount))) {
                    cerr << "Animal already adopted by this person!";
                    break;
                }
                cout << "OK" << endl;
                break;
            }
            case '4': {
                for (const Person &person : zoo.getPeople()) {
                    person.print();
                }
                cout << "OK" << endl;
                break;
            }
            case '5': {
                for (const Animal &animal : zoo.getAnimals()) {
                    animal.print();
                }
                cout << "OK" << endl;
                break;
            }
            case '6': {
                for (const Adoption &adoption : zoo.getAdoptions()) {
                    adoption.print();
                }
                cout << "OK" << endl;
                break;
            }
            case '7': {
                string name;

                cout << "Animal's name:" << endl;
                getline(cin, name);
                if (name == "") {
                    cerr << "Animal's name cannot be blank!";
                    break;
                }
                if (!zoo.hasAnimal(name)) {
                    cerr << "Animal does not exist!" << endl;
                    break;
                }
                Animal animal = zoo.findAnimal(name);
                animal.print();
                for (const Adoption &adoption : zoo.getAdoptions()) {
                    if (adoption.animal.equalTo(animal)) {
                        adoption.adopter.print();
                    }
                }
                cout << "OK" << endl;
                break;
            }
            default:
                cout << "Please choose options 0-7!" << endl;
        }


    }
}


