#include <string>
#include <iostream>
#include "Cat.h"

Cat::Cat(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound) : Animal(animalType, animalName, animalAge, animalWeight, animalBreed, animalColor, animalHealth, animalSound){
    nbrOfCats++;
    myCatNumber = nbrOfCats;
}

int Cat::GetNbrOfCat() const {return nbrOfCats;}
