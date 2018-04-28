//      Roster Number: 24
//
//      Author: Patrick Martinez
//      Due Date:  Apr. 30, 2018
//      Programming Assignment Number 7 - Optional
//
//      Spring 2018 - CS 3358 - 1
//
//      Instructor: Husain Gholoom.
//
//      This program does the following, creates a hash table. Populates hash
//      table halfway with integers from 125 to 425. Displays the array. Allows
//      searching for a value, allows insertion of new numbers, allows deletion
//      of numbers.

#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

/**
Creates a hash table to store and recall integers.
**/
class hash{
private:
    int hash_pos; // The current position of the hash "pointer"
    int array[30];// The array that holds the table
    int numOfHashes; // Number of hashes called
    int numOfCollisions; // Number of rehashes called
    int TABLE_SIZE; // Size of table

    /** These were moved to private since they should not be able to be called
        by end-user **/

    // The hash for the integer passed to the table
    int Hash(int);

    // The rehash formula for when an object can't be inserted into the first
    // position
    int reHash(int);
public:

    // Creates has table populated with '*' to indicate emptiness. It then
    // Iterates through the table and populates half with random integer values
    // between 125-425 inclusive.
    hash(int);

    // Displays prompt for an integer and inserts it to the table
    void insert();

    // Displays prompt and searches for integer in the table
    void search();

    // Displays prompt and deletes integer entered.
    void Delete();

    // Displays hash table array.
    void Display();

    // Returns number of hashes
    int getHashes();

    // Returns number of collisions
    int getCollisions();
};

// Displays menu for option selection.
int displayMenuAndGetOption();

/*****************************************
BEGIN MAIN
*****************************************/
int main () {
    srand(time(NULL)); // Randomize seed

    // Enum to map constants to menu options.
    enum menuOptions
        {DISPLAY = 'a',
         SEARCH,
         INSERT,
         DELETE,
         EXIT = 'x'
         };

    int choice = 0; // Choice entered by user

    hash hashTable(30); // Hashtable generated

    cout << "Welcome to my Hashing Program\n"
         << "\n"
         << "------------------------------\n"
         << "\n"
         << "1. Creates an integer array of size 30. Assigning * to each\n"
         << "   location in the array indicating that the array is empty.\n"
         << "2. Populates half of the array with random integer values\n"
         << "   between 125 and 425 inclusive.\n"
         << "3. If a collision occurs, linear probing will find the next\n"
         << "   available position / location\n"
         << "4. The generated array will be displayed in 2 lines.\n"
         << "   Each line contains 15 numbers separated by 2 spaces.\n"
         << "\n";
    hashTable.Display();
    cout << "\n\n";

    do {
        choice = displayMenuAndGetOption();
        switch(choice) {
            case DISPLAY:
                cout << "\n";
                hashTable.Display();
                cout << "\n\n";
                break;
            case SEARCH:  hashTable.search();
                break;
            case INSERT:  hashTable.insert();
                break;
            case DELETE:  hashTable.Delete();
                break;
            case EXIT:
                break;
            default:
                cout << "\n\n*** Invalid option ***\n\n";
        }
    } while (choice != EXIT);

    cout << "\n\nThe number of times each position / location is hashed when\n"
         << "adding an element in the array is "<< hashTable.getHashes() << "\n"
         << "\n"
         << "The number of linear probes when each number is hashed and \n"
         << "collision occurred when adding an element in the array is "
         << hashTable.getCollisions() << "\n"
         << "\n"
         << "This hashing program was implemented by "
         << "Patrick Martinez - April 30, 2018\n\n";

    return 0;
}

/*****************************************
IMPLEMENTATIONS
*****************************************/

/****************
constructor hash:
    Creates has table populated with '*' to indicate emptiness. It then
    Iterates through the table and populates half with random integer values
    between 125-425 inclusive.
Input: None
Output: None
*****************/
hash::hash(int tableSize) {
    TABLE_SIZE = tableSize;
    numOfHashes = 0;
    numOfCollisions = 0;
    for (int i = 0; i < TABLE_SIZE; i++){
        array[i] = '*';
    }
    for (int i = 0; i < (TABLE_SIZE/2); i++){
        int numToAdd = (rand()%301+125);
        hash_pos = Hash(numToAdd);
        while (array[hash_pos] != '*'){
            hash_pos = reHash(hash_pos);
        }
        array[hash_pos] = numToAdd;
    }
}

/*************
Displays prompt for an integer and inserts it to the table
Input: None
Output: None
*************/
void hash::insert() {
    int data;
    int count = 0;
    cout << "Enter the data to insert: ";
    cin >> data;
    if (data < 125 || data > 425) {
        cout << "\n*** Invalid number entered ***\n\n";
        return;
    }
    hash_pos = Hash(data);
    if (hash_pos >= TABLE_SIZE){
        hash_pos = 0;
    }
    while(array[hash_pos] != '*'){
        hash_pos = reHash(hash_pos);
        count++;
        if(count >= 30){
            cout << "Memory Full!! No space is available for storage";
            break;
        }
    }
    if(array[hash_pos] == '*'){
        array[hash_pos] = data;
    }
    cout << "Data is stored at index " << hash_pos << endl;
}
/************
The hash for the integer passed to the table
Input: Key
Output: Hashed number
************/
int hash::Hash(int key){
    numOfHashes++;
    return key%TABLE_SIZE;
}
/***********
The rehash formula for when an object can't be inserted into the first
position
input: Hashed number
output: rehashed number
**********/
int hash::reHash(int key){
    numOfCollisions++;
    return (key+1)%TABLE_SIZE;
}

/*********
Searches for an integer in the array. If it is found, message is displayed.
If it is not found, negative message displayed.
Input: None
Output: None
**********/
void hash::search(){
    int key, count = 0;
    cout << "Enter a number you want to search (between 125-425): ";
    cin >> key;
    if (key < 125 || key > 425) {
        cout << "\n*** Invalid number entered ***\n\n";
        return;
    }
    hash_pos = Hash(key);
    cout << "\n";
    if (array[hash_pos] == key) {
        cout << "The number " << key << " was found in element " << hash_pos;
        count++;
    } else {
        while(count < TABLE_SIZE + 1) {
            hash_pos = reHash(hash_pos);
            count++;
            if (array[hash_pos] == key) {
                cout << "The number " << key << " was found in element "
                << hash_pos;
                break;
            } else {
                if (count > TABLE_SIZE)
                    cout << key << " was not found.";
            }
        }
    }
    cout << "\n\n";
}

/**********
Displays prompt and deletes integer entered.
Input: None
Output: None
**********/
void hash::Delete(){
    int key, count = 0;
    cout << "Enter a number you want to delete (between 125-425): ";
    cin >> key;
    if (key < 125 || key > 425) {
        cout << "\n*** Invalid number entered ***\n\n";
        return;
    }
    hash_pos = Hash(key);
    cout << "\n";
    if (array[hash_pos] == key) {
        array[hash_pos] = '*';
        cout << key << " has been deleted.";
        count++;
    } else {
        while(count < TABLE_SIZE + 1) {
            hash_pos = reHash(hash_pos);
            count++;
            if (array[hash_pos] == key) {
                array[hash_pos] = '*';
                cout << key << " has been deleted.";
                break;
            } else {
                if (count > TABLE_SIZE)
                    cout << key << " was not found.";
            }
        }
    }
    cout << "\n\n";
}

/*******
Displays the array
Inputs: None
Outputs: None
********/
void hash::Display(){
    cout << "Displaying the generated Array\n"
         << "---------------\n"
         << "\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (array[i] == '*')
            cout << '*' << "  ";
        else
            cout << array[i] << "  ";
        if (i == 15)
            cout << "\n";
    }
}
/*********
Returns number of hashes
*********/
int hash::getHashes() { return numOfHashes; }

/*********
Returns number of collisions
*********/
int hash::getCollisions(){ return numOfCollisions; }

/*********
Creates menu and returns choice
*********/
displayMenuAndGetOption(){
    char choice = 0;

    cout << "Select from the following menu options\n\n"
         << "A.  Display the generated array.\n"
         << "B.  Search for a new number (between 125-425) in the array.\n"
         << "C.  Insert a new number (between 125-425) in the array.\n"
         << "D.  Delete a number (between 125-425) from the array.\n"
         << "X.  End the program.\n"
         << "\n"
         << "Select your option: ";
    cin >> choice;

    switch(choice){
        case 'A': choice = 'a';
            break;
        case 'B': choice = 'b';
            break;
        case 'C': choice = 'c';
            break;
        case 'D': choice = 'd';
            break;
        case 'X': choice = 'x';
            break;
    }

    return choice;
}
