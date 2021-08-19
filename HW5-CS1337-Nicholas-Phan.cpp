/*
1. Nicholas Phan
2. Animal Guessing Game
3. 4/4/2021
4. CS1337.010
5. Changelog - 4/4 Created program
               4/6 Wrote the entire program pretty much
6. Notes - Asks questions to determine if it is an animal, if it is not the animal, input a new question to differentiate and then
            input a new animal. Creates a binary tree with these two methods.
7. Comments - This was really confusing at first, but thank god for Dr. DeGroot.
*/

#include <iostream>
#include <iomanip>
#include <string> //string
#include <sstream> //string stream
#include <cctype>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
using namespace std;

bool done=false; //variable to determine whether or not to terminate the game

struct animalNode { //structure for animal nodes

    string question; //a question to ask the user
    string guess; //the name of an animal to guess
    animalNode* yesAnswer; //null or pointer to the “yes” animalNode (LEFT)
    animalNode* noAnswer; //null or pointer to the “no” animalNode (RIGHT)

};

/*void dumpnode(animalNode* curNode) {
    cout << curNode->question << endl;
    cout << curNode->guess << endl;
}*/

animalNode* askQuestion(animalNode *curNode); //prototype

void playGame(animalNode *curNode) { //main playing function, passes in a node to be looked at

    if (curNode->question!=""){ //if the current node is a question node
        askQuestion(curNode); //ask the question
        return;
    }
    cout << "Is it a(n) " << curNode->guess << "? (y/n)" << endl; //outputs the guess from the struct passed in and asks if it is correct
    char c;
    cin >> c;
    while (!(c=='y' || c=='n')) { //input validation
            cout << "Invalid input! (y/n)" << endl;
            cin >> c;
        }
    if(tolower(c) == 'y') { //if the guess is correct
        // game over we win
        cout << "I won! Thanks for playing. Leave your money at the door -Dr. DeGroot" << endl;
        cout << "Play again? (y/n)" << endl; //allows replays
        char d;
        cin >> d;
        while (!(d=='y' || d=='n')) {
            cout << "Invalid input! (y/n)" << endl;
            cin >> d;
        }
        if (d=='n') //if not wanting to play again, bool function says the game is over
            done=true;
        else if (d=='y') //else, restart from the beginning
            return;
    }
    else { //if the guess is incorrect
        curNode->noAnswer = new animalNode(); //create a new blank animalNode that is pointing from the noAnswer of the passed in struct
        curNode->yesAnswer = new animalNode(); //create a new blank animalNode that is pointing from the yesAnswer of the passed in node
        string animal;
        cin.ignore(); //to ignore whitespace from previous cin
        cout << "What animal were you thinking of?" << endl;
        getline(cin, animal); //gets the new animal we couldn't guess
        cout << "What is a yes/no question that I can use to tell a(n) " << curNode->guess << " from a(n) " << animal << "?" << endl;
        string q;
        getline(cin, q); //gets a new question to differentiate between our guess and the correct animal
        curNode->question = q; //makes the curNode question the NEW question
        cout << "For a(n) " << animal << ", is the answer yes or no? (y/n)" << endl; //gets the answer to that NEW question for the NEW animal
        char a;
        cin >> a;
        while (!(a=='y' || a=='n')) {
            cout << "Invalid input! (y/n)" << endl;
            cin >> c;
        }
        cin.ignore();
        if (a=='y') { //if the answer to the NEW question for the NEW animal is "yes"
            curNode->noAnswer->guess = curNode->guess; //makes the pointer from the noAnswer of the curNode to the new node's guess = the current animal
            curNode->guess = ""; //makes the curNode guess blank
            curNode->yesAnswer->guess = animal; //the guess to the yes answer to the curNode is now the new animal
        }
        else if (a=='n') {
            curNode->yesAnswer->guess = curNode->guess; //makes the pointer from the yesAnswer of the curNode to the new node's guess = the current animal
            curNode->guess = ""; //makes the curNode guess blank
            curNode->noAnswer->guess = animal; //the guess to the no answer to the curNode is now the new animal
        }
    }
    //dumpnode(curNode);
    return;
}

animalNode* askQuestion(animalNode *curNode) {//if we are not making a guess

    cout << curNode->question << endl; //ask the question to see if correct
    char c;
    cin >> c;
    while (!(c=='y' || c=='n')) { //input validation
            cout << "Invalid input! (y/n)" << endl;
            cin >> c;
        }
    if(tolower(c) == 'y') { //if the guess is correct
        playGame(curNode->yesAnswer); //calls the main playing while passing the yesAnswer node
    }
    else { //if the guess is incorrect
        playGame(curNode->noAnswer); //calls the main playing while passing the noAnswer node
    }
}

int main() {

    ofstream myfile ("LOADING.txt");
    struct animalNode root = { "", "Lizard", nullptr, nullptr }; //initializing first root
    while (!done) //keep playing while done=false
        playGame(&root);

}




