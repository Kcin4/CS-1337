// Dog class

#ifndef Dog_H_INCLUDED
#define Dog_H_INCLUDED

#include <string>
#include <iostream>

class Dog : public Animal {
private:
    static int nbrOfDogs; //holds the number of dogs
public:
    int myDogNumber;
    Dog(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound); //constructor for dogs
    int GetNbrOfDogs() const; //getter for number of dogs
};

int Dog::nbrOfDogs = 0; //initializing the number of dogs to 0

#endif
