#include <iostream>
#include <conio.h>
#include <windows.h>
// 1. Snake
// 2. Nicholas Phan
// 3. 2/5/2021
// 4. CS1337.010
// 5. Improving the snake game program
// 6. Changelog -
// 2/5 added comments to more easily understand program
//        didnt change the logic
//        elaborated function names
//        improved white space
// 2/7 added number of fruits capabilities
//        improved snake growing part of logic, added comments to growth
//        added capability to input number of fruits
//        separated concerns in the logic
//        added a report at game over and allowed replays
//        added a pause function
//        added instructions for how to play
//        added option thats can be coded in for if the player wants to lose the game if they hit a wall
//        made input routine case insensitive
//        cleaned up code a little bit more
// 7. Notes - cant figure out how to do multiple fruits
//        feature to make walls end the game is only hard coded in right now
// 8. Comments - The program feels a little too long but I'm not quite sure how to make it shorter.
//        I think I could brute force figuring out the multiple fruits thing but every time I try i just break my entire program.
using namespace std;
bool gameOver;
const int width = 20; //game board dimensions
const int height = 20;
int x, y, fruitX, fruitY, score; //position of head and then fruit
int tailX[100], tailY[100]; // array to save the position of the head for the tail to follow
int nTail; //length of the tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; //enumerate function for direction of snake head
eDirection dir; //variable that holds direction of snake
const bool showflowDebugging = false;
int numFruits;

int main();
void Setup();

void showflow(string msg) {
    if (showflowDebugging) {
        cout << "--> " << msg << endl;
        Sleep(100);
    }
}//end showflow

void EndOfGame() {
    showflow("Entered EndOfGame");
    string response;
    cout << "Ran into tail!" << endl;
    cout << "Play again? (y/n)" << endl;
    cin >> response;
    if (response == "y" or response == "Y"){
        system("cls");
        gameOver = false;
        tailX[100] = {};
        tailY[100] = {};
        nTail = 0;
        main();
    }
    if (response == "n" or response == "N")
        gameOver = true;
}//end EndOfGame

void Instructions() {
    cout << "Eat as many fruits as you can!" << endl;
    cout << "Don't hit your tail!" << endl;
    cout << "UP = W" << endl;
    cout << "DOWN = S" << endl;
    cout << "LEFT = A" << endl;
    cout << "RIGHT = D" << endl;
    cout << "Pause = P" << endl;
    cout << "End game = X" << endl;
}//end Instructions

void NumberOfFruits() {
    showflow("Entered NumberOfFruits");
    cout << "# of fruits? (2 to 5)" << endl;
    cin >> numFruits;
}//end NumberOfFruits

void Setup() {
    showflow("Entered Setup");
    gameOver = false;
    dir = STOP;
    x = width / 2; //position of head in the middle
    y = height / 2;
    for (int i = 0; i < numFruits; i++){
        fruitX = rand() % width; //fruit spawned randomly
        fruitY = rand() % height;
    }
    score = 0;
} //end Setup

void DrawTheGameBoard() {
    showflow("Entered DrawTheGameBoard");
    system("cls"); //clears the screen
    for (int i = 0; i < width+2; i++) //drawing the top of the map
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++) { //printing the inside of the map
        for (int j = 0; j < width; j++) {
            if (j == 0) //prints the left side of the wall
                cout << "#";
            if (i == y && j == x) //drawing the head
                cout << "O";
            else if (i == fruitY && j == fruitX) //drawing the fruit
                cout << "F";
            else { //drawing the tail of the snake
                bool print = false; //if we did NOT print the tail
                for (int k = 0; k < nTail; k++) { //determines length of tail
                    if (tailX[k] == j && tailY[k] == i) { //where to draw the tail
                        cout << "o";
                        print = true; //if we DID print the tail
                    }
                }
                if (!print) //drawing blank space in the tail spot if we did NOT print the tail
                    cout << " ";
            }
            if (j == width - 1) //prints the right side of the map
                cout << "#";
        }
        cout << endl; //starts printing the next line
    }
    for (int i = 0; i < width+2; i++) //drawing the bottom of the map
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl; //shows score at the bottom
} //end DrawTheGameBoard

void InputUserStroke() {
    showflow("Entered InputUserStroke");
    if (_kbhit()) { //if keyboard key is pressed
        switch (_getch()) { //switch inputs for directions
        case 'a': //if a is pressed, direction of the head is left etc.
            dir = LEFT;
            break;
        case 'A': //if a is pressed, direction of the head is left etc.
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'D':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'W':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'S':
            dir = DOWN;
            break;
        case 'x': //instantly ends game
            gameOver = true;
            break;
        case 'X':
            gameOver = true;
            break;
        case 'p': //pause input
            getch();
            break;
        case 'P':
            getch();
            break;
        }
    }
} //end InputUserStroke

void checkDirection() {
    showflow("Entered checkDirection");
    switch (dir) { //switch function for directions
    case LEFT:
        x--; //decreases x value of head when direction is LEFT etc.
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
}//end checkDirection

void checkIfHitWall() {
    showflow("Entered checkIfHitWall");
    //if (x > width || x < 0 || y > height || y < 0) THIS IS IF YOU WANT TO END GAME IF HITTING WALL INSTEAD OF SKIPPING
    //  gameOver = true;
    if (x >= width) x = 0; //CURRENTLY THE GAME WILL TELEPORT IF HITTING A WALL
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;
}//end checkIfHitWall

void checkIfHitTail() {
    showflow("Entered checkIfHitTail");
    for (int i = 0; i < nTail; i++) //game over condition if head hits the tail
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
}//end checkIfHitTail

void checkIfEatenFruit(){
    if (x == fruitX && y == fruitY) { //when the head position matches a fruit
        showflow("checking if I've eaten any fruits");
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; //increase size of tail if fruit is eaten
    }
}//checkIfEatenFruit

void TailGrowth() {
    showflow("Entered Logic");
    int prevX = tailX[0]; //saving the previous position of the snake head in an array to draw where the tail is going
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; //saves the first part of the tail as the current head position
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) { //starts at 1 because we already have something in 0 in the array and tail must be smaller than the tail size
        prev2X = tailX[i]; //drawing the tail to follow the segment before it
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    checkDirection();
    checkIfHitWall();
    checkIfHitTail();
    checkIfEatenFruit();
} //end TailGrowth/logic

int main() {
    Instructions();
    NumberOfFruits();
    Setup(); //main function to just call all functions and set up the game
    while (!gameOver) {
        DrawTheGameBoard();
        InputUserStroke(); //check what user wants to do
        TailGrowth(); //check if hit tail or wall or fruits
        Sleep(10); //sleep(10); slows down the game
    }
    if (gameOver)
        EndOfGame();
    return 0;
} //end Main
