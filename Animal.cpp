#include <string>
#include <iostream>
#include "Animal.h" //uses the library of Animal.h

void Animal::Speak() { //function that outputs the attributes of objects
    if (name=="unknown") //if any of the attributes are unknown, the animal will say they do not know, otherwise they output their attributes
        cout << "I do not have a name." << endl;
    else
        cout << "Hello! My name is " << name << "." <</*<< " and I am a(n) " << color << " " << breed << " " << type << */endl;
    if (type=="unknown")
        cout << "I do not know what type of animal I am." << endl;
    else
        cout << "I am a(n) " << type << "." << endl;
    if (age==0)
        cout << "I do not know how old I am." << endl;
    else
        cout << "I am " << age << " year(s) old." <</*" years old and weigh " << weight << " pound(s)." <<*/ endl;
    if (weight==0)
        cout << "I do not know how much I weigh." << endl;
    else
        cout << "I weigh " << weight << " pound(s)." << endl;
    if (breed=="unknown")
        cout << "I do not know what breed I am." << endl;
    else
        cout << "My breed is " << breed << "." << endl;
    if (color=="unknown")
        cout << "I do not know what color I am." << endl;
    else
        cout << "I am " << color << " in color." << endl;
    if (health=="unknown")
        cout << "My health is unknown." << endl;
    else
        cout << "My health record: " << health << endl;
    if (sound=="")
        cout << "I like to go *Grrrrrrrr*" << endl;
    else
        cout << "I like to go *" << sound << "*" << endl;
    cout << endl;
} //just a bunch of formatted outputs

void Animal::setAnimalType(string animalType) { //SETTERS FOR IF YOU WANT TO INDIVIDUALLY ADD ATTRIBUTES TO AN OBJECT
    type = animalType;
}

void Animal::setAnimalName(string animalName) {
    name = animalName;
}

void Animal::setAnimalAge(int animalAge) {
    age = animalAge;
}

void Animal::setAnimalWeight(int animalWeight) {
    weight = animalWeight;
}

void Animal::setAnimalBreed(string animalBreed) {
    breed = animalBreed;
}

void Animal::setAnimalColor(string animalColor) {
    color = animalColor;
}

void Animal::setAnimalHealth(string animalHealth) {
    health = animalHealth;
}

void Animal::setAnimalSound(string animalSound) {
    sound = animalSound;
}


Animal::Animal(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound) { //SETTER IF YOU WANT TO ADD AN OBJECT WITH ALL ATTRIBUTES ALREADY KNOWN
    type = animalType;
    name = animalName;
    age = animalAge;
    weight = animalWeight;
    breed = animalBreed;
    color = animalColor;
    health = animalHealth;
    sound = animalSound;
}

Animal::Animal() { //setter if you want to add an object with unknown attributes, will set them to default values
    type = "unknown";
    name = "unknown";
    age = 0;
    weight = 0;
    breed = "unknown";
    color = "unknown";
    health = "unknown";
    sound = "*heavy breathing*";
}
