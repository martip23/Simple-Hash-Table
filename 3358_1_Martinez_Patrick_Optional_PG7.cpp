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
using namespace std;

class hash{
private:
    int hash_pos;
    int array[40];
public:
    hash();
    void insert();
    void search();
    int Hash(int);
    int reHash(int);
    void Delete();
    void Display();
};

int main () {
    return 0;
}

hash::hash() {
    for (int i = 0; i < 40; i++){
        array[i] = '*';
    }
}

void hash::insert() {
    int data
    int count = 0;
    cout << "Enter the data to insert: ";
    cin >> data;
    hash_pos = Hash(data);
    if (hash_pos >= 40){
        has_pos = 0;
    }
    while(array[hash_pos] != '*'){
        hash_pos = reHash(hash_pos);
        count++;
        if(count >= 40){
            cout << "Memory Full!! No space is available for storage";
            break;
        }
    }
    if(array[hash_pos] == '*'){
        array[hash_pos] = data;
    }
    cout << "Data is stored at index " << hash_pos << endl;
}

int hash::Hash(int key){
    return key%100;
}

int hash::reHash(int key){
    return (key+1)%100;
}

void hash::search(){
    int key,i;
    bool isFound = false;
    cout << "Enter the key to search: ";
    cin >> key;
    for(int i = 0; i < 40; i++) {
        if(array[i] == key) {
            isFound = true;
            break;
        }
    }
    if(isFound){
        cout << "The key is found at index " << i << endl;
    } else {
        cout << "No record found!!" << endl;
    }
}

void hash::Delete(){
    int key, i;
    bool isFound = false;
    cout << "Enter the key to delete: ";
    cin >> key;
    for (i = 0; i < 40; i++){
        if (array[i] == key){
            isFound = true;
            break;
        }
    }
    if(isFound){
        array[i] = '*';
        cout << "The key is deleted" << endl;
    } else {
        cout << "No key is found!!";
    }
}

void hash::Display(){
    for (int i = 0; i < 40; i++)
        cout << array[i] << "  ";
}
