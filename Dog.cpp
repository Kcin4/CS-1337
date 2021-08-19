#include <string>
#include <iostream>
#include "Dog.h"

Dog::Dog(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound) : Animal(animalType, animalName, animalAge, animalWeight, animalBreed, animalColor, animalHealth, animalSound){
    nbrOfDogs++; //counter for number of dogs when added
    myDogNumber = nbrOfDogs; //saves the number of the dog
}

int Dog::GetNbrOfDogs() const {return nbrOfDogs;} //getter for number of dogs
