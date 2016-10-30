//
// Created by Jan Horvath on 06-Oct-16.
//

#include "handler.h"
#include "zoo.h"
#include <iostream>

using namespace std;

void addPersonAction(Zoo &zoo) {
  string name;
  string email;
  string city;

  cout << "Name:" << endl;
  getline(cin, name);
  if (name.empty()) {
    cerr << "Name cannot be blank!";
    return;
  }

  cout << "Email:" << endl;
  getline(cin, email);
  if (email.empty()) {
    cerr << "Email cannot be blank!";
    return;
  }

  cout << "City:" << endl;
  getline(cin, city);

  if (zoo.hasPerson(email)) {
    cerr << "Person already exists in database." << endl;
    return;
  }
  zoo.addPerson(Person(name, email, city));
  cout << "OK" << endl;
} // 1
void addAnimalAction(Zoo &zoo) {
  string name;

  string description;
  cout << "Name:" << endl;
  getline(cin, name);
  if (name.empty()) {
    cerr << "Name cannot be blank!";
    return;
  }

  cout << "Description:" << endl;
  getline(cin, description);

  if (zoo.hasAnimal(name)) {
    cerr << "Animal already exists in database." << endl;
    return;
  }
  zoo.addAnimal(Animal(name, description));
  cout << "OK" << endl;
} // 2
void adoptAction(Zoo &zoo) {
  string email;
  string name;
  string amountString;
  unsigned int amount;

  cout << "Existing person's email:" << endl;
  getline(cin, email);
  if (email.empty()) {
    cerr << "Email cannot be blank!" << endl;
    return;
  }
  if (!zoo.hasPerson(email)) {
    cerr << "Person does not exist!" << endl;
    return;
  }

  cout << "Animal's name:" << endl;
  getline(cin, name);
  if (name.empty()) {
    cerr << "Animal's name cannot be blank!";
    return;
  }
  if (!zoo.hasAnimal(name)) {
    cerr << "Animal does not exist!" << endl;
    return;
  }

  cout << "Amount donated:" << endl;
  getline(cin, amountString);
  amount = stoi(amountString);

  Person person = zoo.findPerson(email);
  Animal animal = zoo.findAnimal(name);
  if (!zoo.adopt(Adoption(person, animal, amount))) {
    cerr << "Animal already adopted by this person!";
    return;
  }
  cout << "OK" << endl;
} // 3
void printPeopleAction(const Zoo &zoo) {
  for (const Person &person : zoo.getPeople()) {
    std::cout << person;
  }
  cout << "OK" << endl;
} // 4
void printAnimalsAction(const Zoo &zoo) {
  for (const Animal &animal : zoo.getAnimals()) {
    cout << animal;
  }
  cout << "OK" << endl;
} // 5
void printAdoptionsAction(const Zoo &zoo) {
  for (const Adoption &adoption : zoo.getAdoptions()) {
    cout << adoption;
  }
  cout << "OK" << endl;
} // 6
void getAdoptersForPlaqueAction(const Zoo &zoo) {
  string name;

  cout << "Animal's name:" << endl;
  getline(cin, name);
  if (name.empty()) {
    cerr << "Animal's name cannot be blank!";
    return;
  }
  if (!zoo.hasAnimal(name)) {
    cerr << "Animal does not exist!" << endl;
    return;
  }
  Animal animal = zoo.findAnimal(name);
  cout << animal;
  for (const Person &person : zoo.getAdoptersForPlaque(animal)) {
    std::cout << person;
  }
  cout << "OK" << endl;
} // 7

void Handler::handle() {
  char choice = '9';
  std::string input;

  Zoo zoo;

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
      addPersonAction(zoo);
      break;
    }
    case '2': {
      addAnimalAction(zoo);
      break;
    }
    case '3': {
      adoptAction(zoo);
      break;
    }
    case '4': {
      printPeopleAction(zoo);
      break;
    }
    case '5': {
      printAnimalsAction(zoo);
      break;
    }
    case '6': {
      printAdoptionsAction(zoo);
      break;
    }
    case '7': {
      getAdoptersForPlaqueAction(zoo);
      break;
    }
    default:
      cout << "Please choose options 0-7!" << endl;
    }
  }
}
