/*
1. Nicholas Phan
2. Animal Shelter
3. 5/1/2021
4. CS1337.010
5. Changelog - 5/1 Created classes and .h files
               5/2 Wrote the main.cpp
6. Notes - Inputs data from a .csv to create a database of animals and their characteristics by
            inputting them into a classes of animals, dogs, and cats.
7. Comments - Took longer than I expected.
*/
#include <iostream>
#include <iomanip>
#include <cmath> //math
#include <fstream> //file stream
#include <string> //string
#include <sstream> //string stream
#include <vector>
#include "Animal.cpp"
#include "Dog.cpp"
#include "Cat.cpp"

using namespace std;

vector<string> line; //vector of lines from the .csv
vector<Animal> Animals; //vectors of animals and the subclasses of animals
vector<Animal> Cats;
vector<Animal> Dogs;

void readInLines() { //reads in the .csv file

    ifstream input("Animal Shelter Data-05.csv"); //input file stream
    string inString; //string to hold the line
    if (input.is_open()) { //if the input file is open
        getline (input, inString);
        while (getline (input, inString)) //get the line and save it as the inString
            line.push_back(inString); //save the inString into the vector
    }
    input.close();
}

void lineProcessing(string inputLine) { //main processing of putting the data into the classes and objects by receiving a line from the .csv
    //cout << inputLine << endl;
    Animal toBeInput; //creates an Animal
    string inputValue;
    int commaIndex=0, prevIndex=0, nbrOfCommas=0; //index variables
    //cout << inputLine.size() << endl;
    //cout << inputLine << endl;
    for (int i=0; i<inputLine.size(); i++) { //for each character in the line
        if (inputLine[i]==',') { //if it is a comma
            nbrOfCommas++;
            commaIndex = i; //where the comma was found
            //cout << "commaIndex: " << commaIndex << endl;
            //cout << "i: " << i << endl;
            //cout << "prevIndex: " << prevIndex << endl;
            inputValue = inputLine.substr(prevIndex, commaIndex-prevIndex); //the word/number in between the commas is saved as the inputValue
            //cout << inputValue << endl;
            prevIndex = commaIndex+1; //the character that is in front of the last comma that was found
            //cout << nbrOfCommas << endl;
            if (nbrOfCommas==1 && inputValue!="") //separate the columns by data type by using how many commas found
                toBeInput.setAnimalType(inputValue); //inputs the string into the type
            else if (nbrOfCommas==2 && inputValue!="")
                toBeInput.setAnimalName(inputValue); //inputs the string into the name etc.
            else if (nbrOfCommas==3 && inputValue!=""){
                //cout << inputValue;
                toBeInput.setAnimalAge(stoi(inputValue)); //changes the string to an integer value and inputs it into the animal's age
            }
            else if (nbrOfCommas==4 && inputValue!="")
                toBeInput.setAnimalWeight(stoi(inputValue)); //same as above but with weight
            else if (nbrOfCommas==5 && inputValue!="")
                toBeInput.setAnimalBreed(inputValue);
            else if (nbrOfCommas==6 && inputValue!="")
                toBeInput.setAnimalColor(inputValue);
            else if (nbrOfCommas==7 && inputValue!=""){
                toBeInput.setAnimalHealth(inputValue);
                toBeInput.setAnimalSound(inputLine.substr(commaIndex+1, inputLine.size())); //after reaching the last column, input all characters from then on into the sound attribute
            }
            /*else if (nbrOfCommas==7 && commaIndex<inputLine.size()) {
                inputValue = inputLine.substr(commaIndex+1, inputLine.size());
                toBeInput.setAnimalSound(inputValue);
            }*/
        }
    }
    Animals.push_back(toBeInput); //inputs all animals into a vector
    if (toBeInput.type=="dog") //if the animal's type is a dog
        Dogs.push_back(toBeInput); //adds the animal to the dog vector
    else if (toBeInput.type=="cat") //same as above but with cats
        Cats.push_back(toBeInput);
}


int main() {

    readInLines();
    for (int i=0; i<line.size(); i++) //sends all lines from the .csv to the processing function
        lineProcessing(line.at(i));

    //cout << "Number of animals created: " << Animals.size() << endl;
    //cout << "Number of cats created: " << Cats.size() << endl; //***************REPORT 1*****************
    //cout << "Number of dogs created: " << Dogs.size() << endl;

    //for (int i=0; i<Cats.size(); i++) //REPORTING CATS
        //Cats.at(i).Speak();

    //for (int i=0; i<Dogs.size(); i++) //REPORTING DOGS
        //Dogs.at(i).Speak();

    for (int i=0; i<Animals.size(); i++) //REPORTING ALL ADOPTABLE ANIMALS WITH GOOD HEALTH
        if (Animals.at(i).health=="good")
            Animals.at(i).Speak();


/*    Animal test;
    test.setAnimalType("dog");
    cout << test.type;

    for (int i=0; i<line.size(); i++) {
        cout << line.at(i);
        cout << endl;
    }
    Animal test("cat", "Morris", 9, 3, "mixed", "yellow", "good", "bark");
    test.Speak();
    Dog doggytest("dog", "Mittens", 1, 1, "Calico", "brown and orange", "good", "meow");
    doggytest.Speak();
    Cat awef("ye", "the man", 1, 1, "wt", "brown and orange", "tee lit", "suh dude");
    awef.Speak();
    cout << endl;
    cout << doggytest.GetNbrOfDogs();
    cout << endl << doggytest.myDogNumber;
    */
}




