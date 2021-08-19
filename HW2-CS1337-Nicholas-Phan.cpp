/*
1. Nicholas Phan
2. Word Search
3. 2/26/2021
4. CS1337.010
5. Changelog - 2/26 Created main function and read-in function
               2/28 created convert and start search function
               3/2 started the searchGrid function
               3/4 finished program and cleaned all bugs etc.
6. Notes - The program reads in the rows and columns and then reads in the grid and
           prints out the grid, it reads in the movies and makes a copy of the list
           and then removes the spaces and creates a new list. The program starts
           searching at each space for the first letter and then records if it succeeds
           and the direction it succeeds in. If it fails, the movie is saved and results
           are reported at the end.
7. Comments - I am actually really proud of this program, I think it works really well
              and I wrote it completely from scratch and it was really hard.
*/
#include <iostream>
#include <iomanip>
#include <cmath> //math
#include <fstream> //file stream
#include <string> //string
#include <sstream> //string stream
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
string dataFileName; //the file we are opening
int x=0, y=0, MovieCounter=0, UnfoundCounter=0; //row, columns, total movies, # of movies that were not found
int xdir[] = {-1, -1, -1, 0, 1, 1, 1, 0}; //direction arrays
int ydir[] = {-1, 0, 1, 1, 1, 0, -1, -1};
string directionNames[] = {"NW", "N", "NE", "E", "SE", "S", "SW", "W"};
string Movies[50], MoviesTwo[50]; //array to hold the movie names, copy
char GridArray[50][50]; //matrix for the search grid
vector<string> UnfoundMovies; //vector for movies that were not found

void skipAnyCommentLines(ifstream &infile) { //skips comment lines starting with # or that are blank
    string textLine;
    char ch;
    ch = infile.peek();
    while (ch == '#' || ch == '\n') { //check for both comment lines and blank lines
    getline(infile,textLine); //ignore this line - just toss it
    ch = infile.peek(); //peek at first character of next line
    }
}

bool searchGrid(int row, int col, string movie, int &directionIndex) {//actual input of words to search in the matrix
    int length = movie.length();//getting the length of the movie name
    if (GridArray[row][col] != movie[0]) //searching every position given for the starting letter of a movie
        return false; //if it doesn't exist
    for (int i=0; i<8; i++) { //after finding the letter, will search in each direction with the index
        int letterIndex, xPosition = row + xdir[i], yPosition = col + ydir[i]; //index, board position searching in
        for (letterIndex=1; letterIndex<length; letterIndex++) { //loop for searching in each direction after letter is found
            if (xPosition>=x or xPosition<0 or yPosition>=y or yPosition<0) //if you hit a wall, breaks loop
                break;
            if (GridArray[xPosition][yPosition] != movie[letterIndex])//if one of the letters in the direction is not matched, break
                break;
            xPosition += xdir[i]; //moving position of letter being read after each loop to match its directional input
            yPosition += ydir[i];
        }
        if (letterIndex == length){ //if the all of the previous matches and the length of the word matches what has been found
            directionIndex = i; //pass by reference returning the direction to the output
            return true;
        }
    }
    return false;
}

void startSearch(string movieName, int movieLength, int index) { //movie name without spaces, length of name of movie, index position of movie being searched
    int directionValue; //index for direction
    for (int i=0; i<x; i++) { //for each row
            for (int j=0; j<y; j++) //for each column
                if (searchGrid(i, j, movieName, directionValue)) { //sends the row and column being searched and the movie name without spaces
                    cout << MoviesTwo[index] << " found at " << i+1 << ", " << j+1 << ": (direction = " << directionNames[directionValue] << ")" << endl; //outputs found movies
                    Movies[index] = "FOUND"; //crosses the movie off the list by changing it
                }
                else if (i==x-1 && j==y-1 && Movies[index]!="FOUND"){ //if you reach the end of the grid and the movie has yet to be found
                    UnfoundMovies.push_back(Movies[index]); //add unfound movies to the vector
                    UnfoundCounter++; //counts how many unfound movies there are
                }
    }
}

void convertSearch(string str, int index) { //removes spaces from movie names
    str.erase(remove(str.begin(),str.end(),' '),str.end());
    int mLength = str.length(); //gets length of the movie
    startSearch(str, mLength, index);
}

void readFile() {
    cout << "Enter input file name or path" << endl; // prompting input file name
    cin >> dataFileName; // user inputting file name
    ifstream infile; //streaming input file
    infile.open(dataFileName); //opening input file
    while(!infile.is_open()){ //if the file fails to open
        perror ("The following error occurred"); //error message output
        cout << dataFileName << " cannot be found or opened" << endl;
        cout << "Enter input file name or path (or type quit to exit)" << endl; // prompting input file name again
        cin >> dataFileName;
        if (dataFileName=="quit") //if user would like to exit instead
            break;
        infile.open(dataFileName); //opening input file
    }
    cout << endl;
    while(infile.good()) { //while the file is opened
        skipAnyCommentLines(infile);
        infile >> x >> y; //inputs the row and column measurements
        skipAnyCommentLines(infile);
        for (int i=0; i<x; i++) { //loop for inputting the grid data
            for (int j=0; j<y; j++){
                infile >> GridArray[i][j];
                skipAnyCommentLines(infile);
            }
        }
        for (int i=0; i<x; i++) { //loop for drawing board
            for (int j=0; j<y; j++) {
                cout << GridArray[i][j];
                if (j==y-1)
                    cout << endl;
            }
        }
        cout << endl;
        skipAnyCommentLines(infile);
        while(infile){ //loop for inputting the movies into a list
            getline(infile, Movies[MovieCounter]);
            MovieCounter++;
            skipAnyCommentLines(infile);
        }
        for (int i=0; i<MovieCounter; i++) //makes a copy of the movie list to compare later
            MoviesTwo[i] = Movies[i];
    }
    for (int i=0; i<MovieCounter; i++) //sends movies to function for removing spaces
        convertSearch(Movies[i], i);
}

int main() {
    //freopen ("output.txt","w",stdout); (FOR OUTPUTTING TO TXT FILE)
    readFile();
    if (UnfoundCounter>0){ //loop for outputting movies that are not found
        cout << endl << "Could not find these movies:" << endl;
        for (int i=0; i<UnfoundCounter; i++)
            cout << UnfoundMovies.at(i) << endl;
    }
    //fclose (stdout); (FOR OUTPUTTING TO TXT FILE)
}

