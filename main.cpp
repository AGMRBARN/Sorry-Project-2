/* 
 * File: main.cpp
 * Author: Alma Barnhisel
 * Created on July 29, 2023 
 * Purpose:  Sorry! Board Game Version 8
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

// Not global Constant/Sorry! Card constants :P
const int NUM_PLAYERS = 4;
const int NUM_PAWNS_PER_PLAYER = 4;
const int NUM_CARDS = 45;
const int NUM_SPACES = 60;
const int MAX_PLAYERS = 4;
int Ncard[MAX_PLAYERS] = {0}; // Number of cards in each player's hand
int ppos[NUM_PLAYERS] = {0}; // Array to store the positions of each player on the board


using namespace std;

// Function prototypes
bool GameFin(int plrypos);
float dsplyBd(int p1Pos, int p2Pos);
int drawCrd();
int drawCrd(int minVal, int maxVal); // Overloaded function void mvPlayr(int &plrypos, int cardVal);
void apgize(const string &playrN);
void bubSort(vector<int> &arr, int n);
void selSort(vector<int> &arr, int n);
int linearS(const vector<int> &arr, int target);//linear search
int binaryS(const vector<int> &arr, int target);//binary search 
int cardValue;

//User Libraries

//Global Constants only

//Conversions/Math/Physics

//Execution Begins here
int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<int> p1Hand; // Player 1's hand of cards
    vector<int> p2Hand; // Player 2's hand of cards

    bool useBubSort = true; // Flag to switch between Bubble Sort and Selection Sort

    string p1 = "Player1";
    string p2 = "Player2";
    int p1Pos = 0;
    int p2Pos = 0;
    int cardVal;

    // Add parallel array to track player positions
    int ppos[NUM_PLAYERS] = {0}; // Array to store the positions of each player on the board

    //Display menu
    cout << "Welcome to the game Sorry!" << endl;

    do {
        // Individual game loop for each turn
        do {
            dsplyBd(p1Pos, p2Pos);

            cout << p1 << ", it's your turn. Press 'd' to draw a card: ";
            char drawIt;
            cin >> drawIt;

            switch (drawIt) {
                case 'd':
                case 'D':
                    cardVal = drawCrd(1, 6); // For player 1
                    cout << p1 << " drew a card with value " << cardVal << "." << endl;
                    p1Hand.push_back(cardVal); // Add the drawn card to player 1's hand
                    Ncard[0] = p1Hand.size(); // Update the number of cards in player 1's hand
                    // Sort player 1's hand using either Bubble Sort or
                    //Selection Sort based on the flag
                    if (useBubSort) {
                        bubSort(p1Hand, p1Hand.size());
                    } else {
                        selSort(p1Hand, p1Hand.size());
                    }
                    useBubSort = !useBubSort; // Toggle the flag for the next turn
                    mvPlayr(p1Pos, cardVal);
                    break;
                default:
                    apgize(p1);
            }

            // If player1Position >= 20 Then:
            if (GameFin(p1Pos)) {
                cout << (p1 + " wins! Congratulations!") << endl;
                break;
            }

            dsplyBd(p1Pos, p2Pos);

            cout << p2 << ", it's your turn. Press 'd' to draw a card: ";
            cin >> drawIt;

            switch (drawIt) {
                case 'd':
                case 'D':
                    cardVal = drawCrd(1, 6); // For player 2
                    cout << p2 << " drew a card with value " << cardVal << "." << endl;
                    p2Hand.push_back(cardVal); // Add the drawn card to player 2's hand
                    Ncard[1] = p2Hand.size(); // Update the number of cards in player 2's hand

                    // Sort player 2's hand using either Bubble Sort or Selection Sort based on the flag
                    if (useBubSort) {
                        bubSort(p2Hand, p2Hand.size());
                    } else {
                        selSort(p2Hand, p2Hand.size());
                    }
                    useBubSort = !useBubSort; // Toggle the flag for the next turn
                    mvPlayr(p2Pos, cardVal);
                    break;
                default:
                    apgize(p2);
            }

            // If player2Position >= 20 Then:
            // Display "Player2 wins! Congratulations!"
            if (GameFin(p2Pos)) {
                cout << (p2 + " wins! Congratulations!") << endl;
                break;
            }

        } while (p1Pos < 20 && p2Pos < 20); // Individual game loop continues
        //until either player reaches position 20 or beyond

        // Reset positions and hands for a new game
        p1Pos = 0;
        p2Pos = 0;
        p1Hand.clear();
        p2Hand.clear();

        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y') {
    exitGame(); // Call the exitGame function to exit the program
}

    } while (true); // Main game loop continues indefinitely until the player chooses to quit

    // Display "Game Over! Thanks for playing."
    cout << "Game Over! Thanks for playing." << endl;
    return 0;
}

bool GameFin(int plrypos) {
    return plrypos >= 20;
}
// Function to double each element in the array
void dArray(int arr[], int size) {//double array
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

//The purpose of this function is to visually display the game board with the
//positions of both players so that the players can see their progress and
//positions relative to each other on the board.
float dsplyBd(int p1Pos, int p2Pos) {
    cout << "--------------------------------------" << endl;
    for (int i = 0; i <= 20; ++i) {
        if (i == p1Pos && i == p2Pos) {
            cout << "P1P2 ";
        } else if (i == p1Pos) {
            cout << " P1  ";
        } else if (i == p2Pos) {
            cout << " P2  ";
        } else {
            cout << "  " << i << "  ";
        }
    }
    cout << endl;
    cout << "--------------------------------------" << endl;
}

int drawCrd(int minVal, int maxVal) {
    static bool seedInitialized = false;
    if (!seedInitialized) {
        srand(static_cast<unsigned int>(time(0)));
        seedInitialized = true;
    }

    return (rand() % (maxVal - minVal + 1)) + minVal;
}


void mvPlayr(int &plrypos, int cardVal) {
    // Add static variables for Player 1 and Player 2 total moves
    static int totalMovesP1 = 0;
    static int totalMovesP2 = 0;

    if (plrypos > 20) {
        plrypos = 20;
    }
}

//The purpose of this function is to display a message to the player, prompting 
//them to draw a card and try again when they provide an invalid input or fail to 
//draw a card during their turn in the Sorry! game.

void apgize(const string &playrN) {
    cout << playrN << ", you need to draw a card. Try again." << endl;
}
void exitGame() {
    cout << "Exiting the game. Goodbye!" << endl;
    exit(0); // Terminate the program with exit code 0 (success)
}
//In the context of the Sorry! game, we are using Bubble Sort to sort the 
//player's hand of cards in ascending order, so they can easily see and manage
//their cards during the game.
void bubSort(vector<int> &arr, int n) {
    // Implement bubble sort algorithm
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
//To use both Bubble Sort and Selection Sort at the same time, we can alternate
//between the two sorting algorithms for sorting the player's hand of cards
//in the Sorry! game.
void selSort(vector<int> &arr, int n) {
    // Implement selection sort algorithm
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}
// Linear Search function implementation
//In this code, I've added the linearSearch function, which performs a linear 
//search to find the target value in the array. If the target value is 
//found, it returns the index where it is found; otherwise, it returns -1
//to indicate that the target value is not present in the array.

int linearS(const vector<int> &arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // Found the target value at index i
        }
    }
    return -1; // Target value not found in the array
}
// Binary Search function implementation (Assumes the array is sorted in ascending order)
//the binarySearch function, which performs a binary search on a sorted array.
//This function assumes that the input array is sorted in ascending order.
//If the target value is found, it returns the index where it is found; 
//otherwise, it returns -1 to indicate that the target value is not present in the array.

int binaryS(const vector<int> &arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // Found the target value at index mid
        } else if (arr[mid] < target) {
            left = mid + 1; // Discard the left half of the array
        } else {
            right = mid - 1; // Discard the right half of the array
        }
    }
    return -1; // Target value not found in the array
}
void mvPlayr(int playerIndex, int &plrypos, int cardVal) {
    // Add static variables for Player 1 and Player 2 total moves
    static int totalMovesP1 = 0;
    static int totalMovesP2 = 0;

    if (plrypos > 20) {
        plrypos = 20;
    }

    // Update player's position based on the card value
    ppos[playerIndex] += cardVal;
}