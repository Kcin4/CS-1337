// Animal class

#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;

class Animal { //initializing a class
private:
    static int AnimalNumber; //holds the number for each animal
public:
      string name; //Constructors for all the different attributes wanted to be recorded
      void setAnimalName(string animalName); //parameterized constructors
      int age;
      void setAnimalAge(int animalAge);
      int weight;
      void setAnimalWeight(int animalWeight);
      string breed;
      void setAnimalBreed(string animalBreed);
      string color;
      void setAnimalColor(string animalColor);
      string health;
      void setAnimalHealth(string animalHealth);
      string type;
      void setAnimalType(string animalType);
      string sound;
      void setAnimalSound(string animalSound);
      void Speak(); //calls the speak function
      Animal(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound); //getter for known animals
      Animal(); //getter for animals with unknown attributes
};
#endif
