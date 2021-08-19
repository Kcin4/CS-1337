/*
1. Nicholas Phan
2. String Processing
3. 3/26/2021
4. CS1337.010
5. Changelog - 3/26 Created program
               3/27 Created main, SaveSentences, Processing, and findNumWords
               3/28 Finished the rest of the program
6. Notes - Program takes in lines of sentences and processes them to return the number of words, characters, vowels, consonants,
           punctuation, other characters, and the longest word. It also outputs the sentence again using different structures
           such as changing all the letters to uppercase, lowercase, and even spongebobcase. I also got the leet speak to work,
           although the leet 'y' character does not work.
7. Comments - I hardcoded the exception words, I believe I saw Dr. DeGroot do that in class as well so I hope that's okay. I also
              didn't use a 2d vector but I believe some other students messaged Dr. DeGroot and he said that was fine as well.
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

vector<string> Sentences; //vector to save the sentences
string vowels="aeiouyAEIOUY", consonants="bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ", punctuation=".?!,;:-_()[]{}'\"", //strings to search for when counting the number of certain characters
       letters="aeiouyAEIOUYbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ",
       capitals="AEIOUYBCDFGHJKLMNPQRSTVWXZ";
string Exceptions[100] = {"Spain", "Billy", "Fritos", "Friday's", "Hertford,", "Hereford,", "Hampshire,",
                          "Professor", "Henry", "Higgins", "My", "Fair", "Lady", "(\"Liza\")", "Cockney", "\"Rhine\"" }; //array of exceptions.

void SaveSentences(); //prototype functions
void Processing();
int findNumWords(int index);
string findLongestWords(int index);
int findNumCharacters(int index, string strSearchFor);
void titleCase(int index);
void sentenceCase(int index);
void toggleCase(int index);
void spongebobCase(int index);
void LeetChars(int index);
string LeetLibrary(char ch);

int main() {

    SaveSentences();
    Processing();

}

void SaveSentences(){ //saves the sentences into a vector

    ifstream input("TongueTwisters(1).txt"); //streams the given file
    string inString; //string to hold the sentence
    if (input.is_open()) { //if the input file is open
        while (getline (input, inString)) //get the line and save it as the inString
            Sentences.push_back(inString); //save the inString into the vector
    }
    input.close();

}

void Processing() { //driving function to output

    for (int i=0; i<Sentences.size(); i++) { //for loop for each sentence in the vector
        cout << Sentences.at(i) << endl; //output the sentence by itself
        int numChar = Sentences[i].length(); //get the length of the sentence
        cout << "Number of characters: " << numChar << endl;
        int numWords = findNumWords(i) + 1; //call the findNumWords function to get the number of spaces and adds 1 to get the number of words
        cout << "Number of words: " << numWords << endl;
        string longestWord = findLongestWords(i); //calls function to find the longest word
        cout << "Longest word: " << longestWord << endl;
        int numVowels = findNumCharacters(i, vowels); //when calling the findNumCharacters function,
        cout << "Vowels (" << numVowels << "), ";     //it will pass a string of what it is trying to find in the sentence and return the number of times one of those characters appears in the sentence.
        int numConsonants = findNumCharacters(i, consonants);
        cout << "Consonants (" << numConsonants << "), ";
        cout << "Spaces (" << numWords - 1 << "), "; //just reuses the previous numWords and subtracts 1 to get spaces again
        int numPunctuation = findNumCharacters(i, punctuation);
        cout << "Punctuation (" << numPunctuation << "), ";
        cout << "Other (" << numChar - numVowels - numConsonants - numPunctuation - (numWords - 1) << ") " << endl; //all characters that were not found previously are output here.
        titleCase(i); //calling the Case functions to output a new type of sentence.
        cout << endl;
        sentenceCase(i);
        cout << endl;
        toggleCase(i);
        cout << endl;
        spongebobCase(i);
        cout << endl;
        LeetChars(i);
        cout << endl << endl;
    }

}

int findNumWords(int index) { //finds the number of words in a sentence

    string temp=Sentences.at(index); //converts the element in the vector to a string
    char Test[1000];
    for (int i=0; i<temp.length(); i++) { //converts the string into an array of characters
        Test[i] = temp[i];
    }
    int spaces=0; //counter to hold the return value
    for (int i=0; i<temp.length(); i++) { //for each character in the array...
        if (Test[i] == ' ') //if it is a space, increase the counter
            spaces++;
    }
    return spaces;

}

string findLongestWords(int index) {

    string Longest; //for saving the longest word
    stringstream wordIn(Sentences.at(index)); //breaks the sentence into individual words and streams
    string Words[100];
    int i=0;
    while (wordIn >> Words[i]){ //inputs the individual words from the sentence into an array of strings and increments a counter
        i++;
    }
    Longest = Words[0]; //just making the longest word the first one initially, just for ease
    for (int j=0; j<i+1; j++){ //for loop for going through each word in the array
        if (Longest.length() < Words[j].length()) //if the length of the current longest word is less than the word that is being looked at in the index loop
            Longest = Words[j]; //that word becomes the new longest word
    }
    return Longest;

}

int findNumCharacters(int index, string strSearchFor) { //function to find all kinds of characters from a string, pass in a string of characters

    int charCounter=0; //simple counter
    string temp=Sentences.at(index); //converts the element in the vector to a string
    for (int j=0; j<strSearchFor.length(); j++) //loop for searching for each character in the string passed in, such as vowels etc.
        for (int i=0; i<temp.length(); i++) { //loop search for each position in the temp string (the sentence we're searching in)
            i = temp.find(strSearchFor[j], i); //finds the first occurrence of the character and makes that the next index to search afters, so that it does not repeat
            if (i>=0 && i<=temp.length()) //if it finds the character, it will increment a counter
                charCounter++;
            else //if the index gets out of the bounds, the loop will break and start searching for the next character in the passed in string
                break;
    }
    return charCounter;

}

void titleCase(int index) { //function to convert the first letter of each word into uppercase

    string temp=Sentences.at(index); //converts the element in the vector to a string
    char ch[1000];
    int spaceTest=0, letterTest=0; //essentially bool functions
    cout << "Title Case: ";
    for (int i=0; i<temp.length(); i++) //converts the string into an array of characters
        ch[i] = temp[i];
    for (int i=0; i<temp.length(); i++) { //loop search for each position in the temp string
        letterTest=0; //makes the bool test false at the start of each position search
        for (int j=0; j<letters.length(); j++) //loop for determining if the character at the position is a letter
            if (letters[j]==ch[i]) //this is for when there is punctuation characters at the start of a sword like " and (
                letterTest=1; //if it is a letter, set the test to true

        if (ch[i]==' ') { //if the program encounters a space
            spaceTest=1; //set the test to true
            cout << " ";
        }
        else if (spaceTest==1 && letterTest==1){ //if the character is a letter and there has been a space before it that has not yet been capitalized
            putchar (toupper(ch[i])); //output that capitalized character
            spaceTest=0; //set the space test to false again
        }
        else //if neither of these
            cout << ch[i]; //just output the character
    }

}

void sentenceCase(int index) { //function for making all words lowercase except the exception words

    cout << "Sentence Case: ";
    stringstream wordIn(Sentences.at(index)); //breaks the sentence into individual words and streams
    string Words[100];
    int i=0;
    while (wordIn >> Words[i]){ //adds the individual words into an array and increments a counter
        i++;
    }
    for (int j=0; j<i+1; j++){ //for loop for each word in the array
        int ExceptionTest=0, exIndex=0; //essentially a bool function and an integer to hold an index
        for (int k=0; k<16; k++){ //for each word in the exceptions
            if (Exceptions[k]==Words[j]) { //if the word encountered is an exception
                ExceptionTest=1; //set the test to true
                exIndex=k; //save the index of where the exception word is in its array
            }
        }
        if (ExceptionTest=0) //if it is an exception
            cout << Exceptions[exIndex] << " "; //output the exception word in place of the word in the sentence
        else
            cout << Words[j] << " "; //otherwise, output all other words in lowercase
    }

}

void toggleCase(int index) { //function for making the first letter of each word lowercase and the rest uppercase

    string temp=Sentences.at(index); //converts the element in the vector to a string
    char ch[1000];
    int spaceTest=1, letterTest=0;
    cout << "Toggle Case: ";
    for (int i=0; i<temp.length(); i++) //converts the string into an array of characters
        ch[i] = temp[i];
    for (int i=0; i<temp.length(); i++) { //loop search for each position in the character array
        letterTest=0; //resets the test for if it is a letter back to false at the start of every position
        for (int j=0; j<letters.length(); j++) //loop for searching that position compared to each element in the array of letters
            if (letters[j]==ch[i]) //if that character is a letter
                letterTest=1; //save the variable to true

        if (ch[i]==' ') { //if there is a space
            spaceTest=1; //save a variable to indicate that
            cout << " ";
        }
        else if (spaceTest==1 && letterTest==1){ //if there was a space before this character and it is a letter
            putchar (tolower(ch[i])); //output it as lowercase
            spaceTest=0; //reset the tester for spaces back to false
        }
        else //otherwise, output all characters to uppercase
            putchar (toupper(ch[i]));
    }

}

void spongebobCase(int index) { //function to make a random number of letters uppercase and the others lowercase

    string temp=Sentences.at(index); //converts the element in the vector to a string
    char ch[1000];
    int randomNum=0; //variable to save a random number
    srand(time(0)); //random seed
    cout << "SpongeBoB Case: ";
    for (int i=0; i<temp.length(); i++) //converts the string into an array of characters
        ch[i] = temp[i];
    for (int i=0; i<temp.length(); i++) { //loop search for each position in the character string
        randomNum = rand() % 100 + 1; //save a random number at each position between 1 and 100
        if (randomNum>50) //if that number is >50, output a lowercase character
            putchar (tolower(ch[i]));
        else //otherwise, output an uppercase character
            putchar (toupper(ch[i]));
    }

}

void LeetChars(int index) { //function to convert the characters to leet characters

    string temp=Sentences.at(index); //converts the element in the vector to a string
    char ch[1000];
    int randomNum=0; //variable to save a random number
    srand(time(0)); //random seed
    cout << "Leet Speak: ";
    for (int i=0; i<temp.length(); i++) //converts the string into an array of characters
        ch[i] = temp[i];
    for (int i=0; i<temp.length(); i++) { //loop search for each position in the character string
        randomNum = rand() % 100 + 1; //save a random number at each position between 1 and 100
        if (randomNum>50) //if that number is >50 output the regular character
            cout << ch[i];
        else if (randomNum<=50 && LeetLibrary(ch[i])!="NONE") //else if the random number is <=50, output a character from the leet speak library
            cout << LeetLibrary(ch[i]); //calls the leet library function
        else
            cout << ch[i]; //if LeetLibrary could not find a matching character, just output the regular character
    }

}

string LeetLibrary(char ch) { //this function is passed a character, and if that character matches one in the library, the leet speak character is returned to ouput
    if (ch=='A' || ch=='a')
        return "4";
    else if (ch=='B' || ch=='b')
        return "8";
    else if (ch=='C' || ch=='c')
        return "[";
    else if (ch=='D' || ch=='d')
        return "|)";
    else if (ch=='E' || ch=='e')
        return "3";
    else if (ch=='F' || ch=='f')
        return "|";
    else if (ch=='G' || ch=='g')
        return "6";
    else if (ch=='H' || ch=='h')
        return "#";
    else if (ch=='I' || ch=='i')
        return "1";
    else if (ch=='J' || ch=='j')
        return "_|";
    else if (ch=='K' || ch=='k')
        return "K";
    else if (ch=='L' || ch=='l')
        return "1";
    else if (ch=='M' || ch=='m')
        return "|v|";
    else if (ch=='N' || ch=='n')
        return "|\|";
    else if (ch=='O' || ch=='o')
        return "()";
    else if (ch=='P' || ch=='p')
        return "|*";
    else if (ch=='Q' || ch=='q')
        return "(_,)";
    else if (ch=='R' || ch=='r')
        return "2";
    else if (ch=='S' || ch=='s')
        return "5";
    else if (ch=='T' || ch=='t')
        return "7";
    else if (ch=='U' || ch=='u')
        return "(_)";
    else if (ch=='V' || ch=='v')
        return "\/";
    else if (ch=='W' || ch=='w')
        return "\/\/";
    else if (ch=='X' || ch=='x')
        return "><";
    else if (ch=='Y' || ch=='y')
        return "¥";
    else if (ch=='Z' || ch=='z')
        return "2";
    else
        return "NONE";

}
