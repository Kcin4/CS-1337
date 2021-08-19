// Cat class

#ifndef Cat_H_INCLUDED
#define Cat_H_INCLUDED

#include <string>
#include <iostream>

class Cat : public Animal {
private:
    static int nbrOfCats;
public:
    int myCatNumber;
    Cat(string animalType, string animalName, int animalAge, int animalWeight, string animalBreed, string animalColor, string animalHealth, string animalSound);
    int GetNbrOfCat() const;
};

int Cat::nbrOfCats = 0;

#endif
