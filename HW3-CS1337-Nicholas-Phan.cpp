/*
1. Nicholas Phan
2. Searching & Sorting
3. 3/14/2021
4. CS1337.010
5. Changelog - 3/13 Created program up to bubble sort
               3/14 Finished program
6. Notes - The program generates random numbers and puts them in a vector. It then sorts the vectors
           using two different methods and reports the results. It then searches the vectors for an input
           given by the user and reports the results. It then deletes the duplicates in the vector and reports
           the results.
7. Comments - I'm not sure I found any bugs, perhaps the efficiency of the program could be improved though?
*/
#include <iostream>
#include <iomanip>
#include <cmath> //math
#include <cctype>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int numGen, genMax; //numbers to generate and the maximum number in the vector
vector<int> vec1; //vectors and its copy
vector<int> vec2;

void userPrompt(); //prototype functions
void generateNumbers(int);
void vecSortAlgo();
void bubbleSort();
void findBinary();
void deleteDuplicates();

int main() { //main driver and order of functions
    userPrompt();
    generateNumbers(numGen);
    vecSortAlgo();
    bubbleSort();
    findBinary();
    findBinary();
    findBinary();
    findBinary();
    findBinary();
    deleteDuplicates();
}

void userPrompt() { //input for how many numbers and the max to generate
    cout << "How many numbers would you like to generate? (Min=40)" << endl;
    cin >> numGen; //how many random numbers to generate
    while (numGen<40){ //if the user inputs a number lower than the minimum, prompts a reentry
        cout << "Choose a number greater than or equal to 40!" << endl;
        cin >> numGen;
    }
    cout << "Maximum number? (Max=20)" << endl;
    cin >> genMax; //maximum number to be generated
    while (genMax>20){ //if the user inputs a number that is higher than the max, prompts reentry
        cout << "Max too large!" << endl;
        cout << "Choose another Maximum number (<20)" << endl;
        cin >> genMax;
    }
}

void generateNumbers(int userGenInput) { //generates the random numbers
    srand (time(0)); //random seed
    int numGenerated;
    for (int i=0; i<userGenInput; i++){ //generates the numbers between 1 and the user input max
        numGenerated = rand() % genMax + 1;
        vec1.push_back(numGenerated); //stores in fresh vector
    }
    cout << "Vector Size = " << vec1.size() << endl; //outputs the vector's size, capacity, and contents
    cout << "Vector Capacity = " << vec1.capacity() << endl;
    cout << "Vector Contents: " << endl;
    for (int i=0; i<userGenInput; i++)
        cout << "| " << vec1.at(i) << " ";
    cout << "|";
    vec2 = vec1; //makes a copy of the vector
    cout << endl << endl;
}

void vecSortAlgo() { //sorting the vector with STL
    sort(vec1.begin(),vec1.end());
    cout << "Vector 1 after being sorted: " << endl; //outputs results
    for (int i=0; i<vec1.size(); i++)
        cout << "| " << vec1.at(i) << " ";
    cout << "|";
    cout << endl << endl;
}

void bubbleSort() { //bubble sorting function
    for (int i=0; i<vec2.size()-1; i++) //goes through each position
        for (int j=0; j<vec2.size()-i-1; j++) //looks at the number in each position
            if (vec2.at(j) > vec2.at(j+1)) //if the number is greater then next next number, swaps their positions
                swap(vec2.at(j), vec2.at(j+1));
    cout << "Vector 2 after being bubble sorted: " << endl; //outputs results after being bubble sorted
    for (int k=0; k<vec2.size(); k++)
        cout << "| " << vec2.at(k) << " ";
    cout << "|";
    cout << endl << endl;
}

void findBinary() { //searching the function for a number with binary search method
    int numSearch, numCounter=0; //number to be searched for, how many times it appears
    bool doneSearch=false; //boolean to tell the while loop whether or not it is done
    cout << "Enter number to search for (1 to " << genMax << ")" << endl; //user prompts for number to search for
    cin >> numSearch;
    while (numSearch<1 || numSearch>genMax){ //if the number input is outside of bounds, reprompt
        cout << "Choose another number to search (1 to " << genMax << ")" << endl;
        cin >> numSearch;
    }
    int first = 0, last = vec1.size()-1, middle; //lower bound, upper bound, middle for binary method
    while (!doneSearch && first <= last) { //while loop to search the function until either the bounds close in on each other or pass each other
        middle = (first + last) / 2; //initial middle index
        if (vec1.at(middle)==numSearch) {//if the term being searched for is found at the middle
            numCounter++; //increase how many times its been found
            int i=0, j=0; //new indexes to search around the middle
            while (vec1.at(middle-i)==numSearch){ //while the value to the LEFT of the middle is == the number being searched
                if (i!=0) //add to the counter if it is not the same number as the middle one found
                    numCounter++;
                i++; //increase the index
                if (middle-i<0) //if out of bounds, break the loop
                    break;
            }
            while (vec1.at(middle+j)==numSearch) { //while the value to the RIGHT of the middle is == the number being searched
                if (j!=0) //increase the counter if it is not the same as the middle
                    numCounter++;
                j++; //increase index
                if (middle+j>vec1.size()-1) //if out of upper bound, break loop
                    break;
            }
            doneSearch = true; //break entire while loop
        }
        else if (vec1.at(middle)>numSearch) //if the term being searched for is lower than the term at the middle, sets the new index to search lower half
            last = middle - 1;
        else if (vec1.at(middle)<numSearch) //if the term being searched for is higher, reduce search area to upper half
            first = middle + 1;
    }
    cout << endl << "Was the number " << numSearch << " found in Vector 1?" << endl; //outputs the number of times found or if it was not found
    if (numCounter>0){
        cout << "Response: Yes!" << endl;
        cout << "Number of times found: " << numCounter << endl << endl;
    }
    if (numCounter==0)
        cout << "Response: No." << endl << endl;
}

void deleteDuplicates() { //delete duplicates from the vector
    int index=0;
    while(index<vec1.size()-1){ //while the index is not at the end of the vector
        if (vec1.at(index+1)==vec1.at(index)) //if the value at the index position is the same as the next
            vec1.erase(vec1.begin()+index+1); //erase the next value
        else
            index++; //otherwise, increase the index
    }
    cout << "Vector 1 after deleting duplicates: " << endl; //output vector after duplicates are deleted
    for (int i=0; i<vec1.size(); i++)
        cout << "| " << vec1.at(i) << " ";
    cout << "|";
}
